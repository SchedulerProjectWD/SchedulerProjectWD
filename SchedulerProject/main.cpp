#include <iostream>
#include <thread>
#include <Windows.h>
#include "Task.h" 
#include "Timer.h"
#include "MultiLevelQueue.h"
#include "Scheduler.h"
#include "UI.h"

using namespace std;
atomic_int Timer::time = 0;
int UI::autoId = 0;

int helloWorld(void* a)
{
	cout << "hello world ==== " << Timer::GetTime() << endl;
	return 0;
}

int helloWorldHigh(void* a)
{
	cout << "hello world high priority ==== " << Timer::GetTime() << endl;
	return 0;
}

int lowwww(void* a)
{
	system("Color E4");

	cout << "lowwwwwwwwww ==== " << Timer::GetTime() << endl;
	return 0;
}

void invokeUI(void* param)
{
	UI ui;
	ui((std::condition_variable *)param);
}

void invokeScheduler(void* param)
{
	Scheduler scheduler;
	scheduler.SystemActivation((condition_variable*)param);
}


int main()
{
	cout << "CV MAIN" << &condVar;
	is_active = true;
	//ul.unlock();
	//system("start C:\\eclipse\\eclipse.exe");
	//system("start C:\\Users\\שניידר\\AppData\\Local\\slack\\slack.exe");
	thread thr(invokeUI, &condVar);
	//thread thr1(invokeScheduler, nullptr);
	
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	Scheduler scheduler;
	scheduler.SystemActivation(&condVar);

	thr.join();
	//thr1.join();

	/*Task t(1, 0, helloWorld, 1, 1, 2, nullptr);
	Task t1(1, 0, helloWorldHigh, 1, 1, 70, nullptr);
	Task t2(1, 1, lowwww, 1, 1, 1, nullptr);*/

	//cout << &MultiLevelQueue::getMLQ(30) << endl;
	/*MultiLevelQueue::getMLQ(30).AddNewTask(&t2);
	MultiLevelQueue::getMLQ(30).AddNewTask(&t);
	MultiLevelQueue::getMLQ(30).AddNewTask(&t);
	MultiLevelQueue::getMLQ(30).AddNewTask(&t1);*/

	//cout << MultiLevelQueue::getMLQ(30).getCurrentSize();
	//cout << &MultiLevelQueue::getMLQ(30) << endl;
}
