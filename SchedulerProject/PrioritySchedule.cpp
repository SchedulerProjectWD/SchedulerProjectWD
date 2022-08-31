#pragma once
#include <iostream>
#include "PrioritySchedule.h"
#include "Timer.h"

//c-tor & d-tor
PrioritySchedule::PrioritySchedule(int limitTasksToExec, int limitSize, int closeToStarvation)
	: ScheduleMethod(limitTasksToExec, closeToStarvation, eType::real_time) {
	queue = new MaxHeap<Task>(limitSize);
}

PrioritySchedule::~PrioritySchedule() {
	delete queue;
}

//ScheduleMethod override
int PrioritySchedule::GetNumWaitingTasks() {
	return queue->getSize();
}
bool PrioritySchedule::IsEmpty() { return queue->IsEmpty(); }
Task* PrioritySchedule::ScheduleTask() { return queue->ExtractMax(); }
bool PrioritySchedule::Insert(Task* task) { return queue->Insert(task); }

//insert task which arrives from the high/low queue
bool PrioritySchedule::InsertFromAnotherQueue(Task* task) {
	int currentTime = Timer::GetTime();
	//determine what priority the task would get:
	int task_priority = MAX_TASK_PRIORITY;     //default value

	//check the top 10 tasks in the queue 
	// if there a task that close to starvation
	//set the task_priority to be one less the starved task
	//(which ensures the execution task immediately after)
	Task** highestPriorityTasks = new Task * [MAX_STARVED_TASKS_RT];
	for (int i = 0; i < MAX_STARVED_TASKS_RT; i++)
	{
		highestPriorityTasks[i] = queue->ExtractMax();
		if (highestPriorityTasks[i] == nullptr)
			break;
		int waitingTime = currentTime - highestPriorityTasks[i]->getArriavlTime();
		if (highestPriorityTasks[i] && waitingTime >= closeToStarvation)
			task_priority = min(task_priority, highestPriorityTasks[i]->getPriority() - 1);
	}
	//put back the 10 highest priority tasks that were extracted .
	for (int i = 0; i < 10 && highestPriorityTasks[i]!=nullptr; i++)   
		queue->Insert(highestPriorityTasks[i]);
	task->setPriority(task_priority);
	return queue->Insert(task);
}

bool PrioritySchedule::InsertFromAnotherQueue(LinkedList<Task>* starvedTasks) {

	Node<Task>* ptr = starvedTasks->getHead();
	int len = starvedTasks->getLength();
	while (ptr)
	{
		if (!InsertFromAnotherQueue(ptr->data))
			return false;
		ptr = ptr->next;
	}
	return true;
}

//check the waiting time of tasks .
// change its priority of task which its waiting time is closing to starvation
LinkedList<Task>* PrioritySchedule::DetectSystem(int limit) //the limit variable is not used!
{
	int currentTime = Timer::GetTime();
	int countTasks = queue->getSize();

	for (int i = 0; i < countTasks; i++)
	{
		int waitingTime = currentTime - (*queue)[i]->getArriavlTime();
		if (waitingTime >= closeToStarvation)
			queue->ChangePriority((*queue)[i], MAX_TASK_PRIORITY);
	}
	return nullptr;
}
