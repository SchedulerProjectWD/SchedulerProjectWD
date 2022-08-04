#include "Task.h"
#include "ScheduleMethod.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

class PrioritySchedule :ScheduleMethod
{
private:

	MaxHeap<Task>* queue;
	const int MaxPriority = 200;
public:
	bool IsEmpty();
	~PrioritySchedule();
	PrioritySchedule(int limitTasksToExec, int limitSize, int closeToStarvation);
	Task* ScheduleTask();
	bool Insert(Task* task);
	int GetNumWaitingTasks();
	bool InsertFromAnotherQueue(Task* task);
	LinkedList<Task>* DetectSystem( int limit);
}; 



