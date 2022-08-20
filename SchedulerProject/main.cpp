#include <iostream>
#include "MaxHeap.h"
#include "Queue.h"
#include "Task.h" 
#include "ScheduleMethod.h"
#include "FCFSSchedule.h"
#include "PrioritySchedule.h"
#include "Timer.h"
#include "Logger.h"
#include "Timer.h"
#include "MultiLevelQueue.h"
#include "Scheduler.h"
using namespace std;
int Timer::time = 0;

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
	cout << "lowwwwwwwwww ==== " << Timer::GetTime() << endl;
	return 0;
}

int main()
{
	//Logger log("log.bin");
	//LogRecord rec(INFO, "infoooooooooooooooooooo");
	//LogRecord r;

	//log << rec;
	//rec.setMessage("222222222");
	//log << rec;
	//rec.setMessage( "3333333333");
	//log << rec;
	//rec.setMessage( "44444444");
	//log << rec;
	//cout << "seek: " << log.GetLength() << endl;
	//for (size_t i = 0; i < log.GetLength(); i++)
	//{
	//	log >> r;
	//	cout << r.message << endl;
	//	++log;
	//}
	//LogRecord rec1(INFO, "newww");

	//log << rec1;
	//log >> r;
	//cout << r.message << endl;
	Task t(1, 0, helloWorld, 1, 1, 2, nullptr);
	Task t1(1, 0, helloWorldHigh, 1, 1, 70, nullptr);
	Task t2(1, 1, lowwww, 1, 1, 1, nullptr);
	/*MaxHeap<Task> heap(7);
	Queue<Task> q;
	heap.Insert(&t);
	q.enqueue(&t);
	cout << heap.ExtractMax()->getArriavlTime() << endl;
	cout << q.dequeue()->getArriavlTime() << endl;
	FCFSSchedule f(10, 7, eType::high);
	f.Insert(&t);
	cout << f.ScheduleTask()->getArriavlTime() << endl;
	PrioritySchedule p(10, 15, 6);
	p.Insert(&t);
	cout << p.ScheduleTask()->getArriavlTime() << endl;*/

	//MultiLevelQueue& mlq = MultiLevelQueue::getMLQ(30);
	cout << &MultiLevelQueue::getMLQ(30) << endl;
	MultiLevelQueue::getMLQ(30).AddNewTask(&t2);
	MultiLevelQueue::getMLQ(30).AddNewTask(&t);
	MultiLevelQueue::getMLQ(30).AddNewTask(&t);
	MultiLevelQueue::getMLQ(30).AddNewTask(&t1);
	cout << MultiLevelQueue::getMLQ(30).getCurrentSize();
	cout << &MultiLevelQueue::getMLQ(30) << endl;

	Scheduler scheduler;
	scheduler.SystemActivation();
}
