#include <iostream>
#include "Task.h"
#include "ScheduleMethod.h"
#include "PrioritySchedule.h"
#include "Timer.h"

//c-tor & d-tor
PrioritySchedule::PrioritySchedule(int limitTasksToExec, int limitSize, int closeToStarvation) : ScheduleMethod(limitTasksToExec, closeToStarvation) {
	queue = new MaxHeap<Task>(limitSize);
}
PrioritySchedule::~PrioritySchedule() {
	delete queue;
}

//ScheduleMethod override
int PrioritySchedule::GetNumWaitingTasks() {
	return queue.getSize();
}
bool PrioritySchedule::IsEmpty() { return queue->IsEmpty(); }
Task* PrioritySchedule::ScheduleTask() { return queue->ExtractMax(); }
bool PrioritySchedule::Insert(Task* task) { return queue->Insert(task); }

//insert task which arrives from the high/low queue
inline bool PrioritySchedule::InsertFromAnotherQueue(Task* task) {
	int currentTime=Timer :: currentTime();

	//determine what priority the task would get:
	int task_priority = MaxPriority;     //default value
	    //check the top 10 tasks in the queue 
		// if there a task that close to starvation
		//set the task_priority to be one less the starved task
	   //(which ensures the execution task immediately after)
	Task** highestPriorityTasks = new Task * [10];
	for (size_t i = 0; i < 10; i++)
	{
		
		highestPriorityTasks[i] = queue->extractMax();
		int waitingTime = currentTime- highestPriorityTasks[i]->getArriavlTime();
		if (highestPriorityTasks[i] &&  waitingTime >= closeToStarvation)
			task_priority = min(task_priority, highestPriorityTasks[i]->getPriority() - 1);
	}
	for (size_t i = 0; i < 10; i++)    //put back the 10 highest priority tasks that were extracted .
		queue->insert(highestPriorityTasks[i]);
	task->setPriority(task_priority);
	return queue->insert(task);
}

//check the waiting time of tasks .
// change its priority of task which its waiting time is closing to starvation
inline void PrioritySchedule::DetactSystem(int limit) //the limit variable is not used!
{
	int currentTime = Timer::currentTime();
	int countTasks = queue.getSize();

	for (size_t i = 0; i < countTasks; i++)
	{
		int waitingTime = currentTime - queue[i]->getArrivalTime();
		if (waitingTime >= closeToStarvation) 
			queue->ChangePriority(queue[i], MaxPriority);
	}
}


