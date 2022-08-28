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
#include <functional>
#include "TasksFuncs.h"
using namespace std;

int (*TasksFuncs::functionForTasks[8])(void*) = {
						   TasksFuncs::open_application,
						   TasksFuncs::send_messeg,
						   TasksFuncs::backup_files,
						   TasksFuncs::take_photo,
						   TasksFuncs::download_file,
						   TasksFuncs::low_task,
						   TasksFuncs::high_task,
						   TasksFuncs::realtime_task };

std::ostream& operator<<(std::ostream& os, const PrintIntro p)
{
	system(p.color.c_str());
	os << p.text << endl;
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
	int id;
	cin >> id;
	id--;
	eType newTaskType = (eType)(id % QUEUES_COUNT);

	int newTaskArrivalTime = Timer::GetTime();
	Task* newTask = new Task(autoId++, (int)newTaskType, TasksFuncs::functionForTasks[id], newTaskArrivalTime, 10, 0, nullptr);
	return newTask;
}
bool UI::sendTaskToMLQ(Task* newTask, std::condition_variable* condVarP)
{
	MultiLevelQueue& mlq = MultiLevelQueue::getMLQ(MAX_CAPACITY);
	std::unique_lock<std::mutex> ul(mtx);
	//ul.lock();
	condVarP->wait(ul, std::bind([&mlq, newTask]() {return !(mlq.IsFull(newTask->getType())); }));
	bool success = mlq.AddNewTask(newTask);
	ul.unlock();
	condVarP->notify_all();
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return success;
}

void say_goodbye() {
	cout << SAY_GOODBYE;
}

void UI::operator()(std::condition_variable* condVar)
{
	MultiLevelQueue::getMLQ().isActive = true;// = true;
	printIntro();
	printMenu();
	int input = 1;
	Task* task;
	do
	{
		cin >> input;
		switch (input)
		{
		case 1:
			task = getNewTaskFromUser();
			sendTaskToMLQ(task, condVar);
			printMenu();
			break;
		default:
			break;
		}
	} while (input);
	MultiLevelQueue::getMLQ().isActive = false;// = true;
	condVar->notify_all();
	say_goodbye();
}
