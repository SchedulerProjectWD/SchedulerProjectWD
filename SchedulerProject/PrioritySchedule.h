#include "Task.h"
#include "ScheduleMethod.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include <iostream>

using namespace std;

class PrioritySchedule : public ScheduleMethod
{
private:
	MaxHeap<Task>* queue;
	const int MaxPriority = 200;
	bool InsertFromAnotherQueue(Task* task);
public:
	bool IsEmpty();
	~PrioritySchedule();
	PrioritySchedule(int limitTasksToExec, int limitSize, int closeToStarvation);
	Task* ScheduleTask();
	bool Insert(Task* task);
	int GetNumWaitingTasks();
	bool InsertFromAnotherQueue(LinkedList<Task>* starvedTasks);
	LinkedList<Task>* DetectSystem(int limit);
};
