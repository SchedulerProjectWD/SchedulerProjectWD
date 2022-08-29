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
	system("Color B4");
	time_t now = time(0);
	char currentTime[26] = {};
	ctime_s(currentTime, 26, &now);
	cout << currentTime << endl;
	cout << "The scheduler is turned on." << endl;
}

void UI::printMenu()
{
	cout << GET_TASK_ID;
	cout <<"enter 0 to exit." << endl;
}

Task* UI::getNewTaskFromUser(int id)
{
	id--;
	eType newTaskType = (eType)(id % QUEUES_COUNT);

	int newTaskArrivalTime = Timer::GetTime();
	Task* newTask = new Task(autoId++, (int)newTaskType, TasksFuncs::functionForTasks[id], newTaskArrivalTime, 10, 0, nullptr);
	return newTask;
}
bool UI::sendTaskToMLQ(Task* newTask, std::condition_variable* CVisThereWaitingTask)
{
	MultiLevelQueue& mlq = MultiLevelQueue::getMLQ(MLQ_MAX_CAPACITY);
	std::unique_lock<std::mutex> ul(mtx);
	CVisThereWaitingTask->wait(ul, std::bind([&mlq, newTask]() {return !(mlq.IsFull(newTask->getType())); }));
	bool success = mlq.AddNewTask(newTask);
	ul.unlock();
	CVisThereWaitingTask->notify_all();
	return success;
}

void say_goodbye() {
	cout << SAY_GOODBYE;
}

void UI::operator()(std::condition_variable* CVisThereWaitingTask)
{
	MultiLevelQueue::getMLQ().isActive = true;
	printIntro();
	printMenu();
	int input;
	Task* task;
	cin >> input;
	while (input)
	{
		task = getNewTaskFromUser(input);
		sendTaskToMLQ(task, CVisThereWaitingTask);
		cin >> input;
	}
	MultiLevelQueue::getMLQ().isActive = false;
	CVisThereWaitingTask->notify_all();
	say_goodbye();
}
