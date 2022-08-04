#include <iostream>
#include "MaxHeap.h"
#include "Queue.h"
#include "Task.h" 
#include "ScheduleMethod.h"
#include "FCFSSchedule.h"
using namespace std;

int main()
{
	Task t(1, 1, nullptr, 1, 100);
	MaxHeap<Task> heap(7);
	Queue<Task> q;
	heap.Insert(&t);
	q.enqueue(&t);
	cout << heap.ExtractMax()->getArriavlTime() << endl;
	cout << q.dequeue()->getArriavlTime() << endl;
	FCFSSchedule f(10, 7);
	f.Insert(&t);
	cout << f.ScheduleTask()->getArriavlTime() << endl;
}
