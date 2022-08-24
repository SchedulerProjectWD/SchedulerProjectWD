#include "UI.h"
#include "Timer.h"
#include "constDefinitions.h"
#include "MultiLevelQueue.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <mutex>
#include <condition_variable>
using namespace std;

void UI::printIntro()
{
	system("Color B4");//0F
	time_t now = time(0);
	char currentTime[26] = {};
	ctime_s(currentTime, 26, &now);
	cout << currentTime << endl;
	cout << "The scheduler is turn on." << endl;
}

void UI::printMenu()
{
	cout << "enter 1 to add task.\n" <<
		"enter 0 to exit." << endl;
}

Task* UI::getNewTaskFromUser()
{
	//func priority/timeout
	//choose func
	int time = Timer::GetTime();
	Task* newTask = new Task(autoId++, (int)eType::high, nullptr, time, 0, 0, nullptr);
	return newTask;
}

bool UI::sendTaskToMLQ(Task* newTask)
{
	MultiLevelQueue& mlq = MultiLevelQueue::getMLQ(MAX_CAPACITY);
	std::unique_lock<std::mutex> ul(mtx);
	condVar.wait(ul, [&mlq]() {return !(mlq.IsFull()); });
	bool success = mlq.AddNewTask(newTask);
	ul.unlock();
	return success;
}

void UI::operator()(void* params)
{
	printIntro();
	printMenu();
	int input;
	Task* task;
	do
	{
		cin >> input;
		switch (input)
		{
		case 1:
			task = getNewTaskFromUser();
			sendTaskToMLQ(task);
			break;
		default:
			break;
		}
	} while (input);//
}
