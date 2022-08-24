#include "UI.h"
#include "Timer.h"
#include "constDefinitions.h"
#include "MultiLevelQueue.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <mutex>
#include <condition_variable>
#include  <atomic>
using namespace std;

std::ostream& operator<<(std::ostream& os, const PrintIntro p)
{
	system(p.color.c_str());
	os << p.text<<endl;
	return os;
}

void UI::printIntro()
{
	system("Color B4");//0F
	time_t now = time(0);
	char currentTime[26] = {};
	ctime_s(currentTime, 26, &now);
	cout << currentTime << endl;
	cout << "The scheduler is turned on." << endl;
}

void UI::printMenu()
{
	cout << "enter 1 to add task.\n" <<
		"enter 0 to exit." << endl;
}

Task* UI::getNewTaskFromUser()
{
	cout << GET_TASK_ID;
	int time = Timer::GetTime();
	Task* newTask = new Task(autoId++, (int)eType::high, nullptr, time, 0, 0, nullptr);
	return newTask;
}

bool UI::sendTaskToMLQ(Task* newTask)
{
	MultiLevelQueue& mlq = MultiLevelQueue::getMLQ(MAX_CAPACITY);
	std::unique_lock<std::mutex> ul(mtx);
	condVar.wait(ul, [&mlq,newTask]() {return !(mlq.IsFull( newTask->getType())); });
	bool success = mlq.AddNewTask(newTask);
	ul.unlock();
	return success;
}

void say_goodbye() {
	cout << SAY_GOODBYE;
}

void UI::operator()(void* params)
{
	is_active.store(true);
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
	} while (input);
	is_active.store(false);
	say_goodbye();
}
