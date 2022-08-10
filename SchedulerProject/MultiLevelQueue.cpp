#include "MultiLevelQueue.h"
#include "FCFSSchedule.h"
#include "PrioritySchedule.h"
#include "Task.h"
#include <exception>

MultiLevelQueue::MultiLevelQueue(int maxCapacity ,
							int PriorityLimitTasksToExec, int PriorityCloseToStarvation,
							int FCFSlimitTasksToExec, int FCFScloseToStarvation) 
	:maxCapacity(maxCapacity),currentSize(0)
{
	queues = new ScheduleMethod * [queuesCount];
	queues[0] = new PrioritySchedule(PriorityLimitTasksToExec,maxCapacity,PriorityCloseToStarvation);
	queues[1] = new FCFSSchedule(FCFSlimitTasksToExec,FCFScloseToStarvation ,eType::high);
	queues[2] = new FCFSSchedule(FCFSlimitTasksToExec, FCFScloseToStarvation, eType::low);
}

bool MultiLevelQueue::IsEmpty() {
	return currentSize == 0;
}

bool MultiLevelQueue::IsFull() {
	return currentSize == maxCapacity;
}

int MultiLevelQueue::getMaxCapacity() {
	return maxCapacity;
}

int MultiLevelQueue::getCurrentSize()
{
	return currentSize;
}

void MultiLevelQueue::decreaseCurrentSize() {
	currentSize--;
}

bool MultiLevelQueue::AddNewTask(Task* newTask) {
	try
	{
		bool result = false;
		int i = 0;
		while (i < queuesCount)
		{
			if (newTask->getType() == queues[i]->getType())
				result = queues[i]->Insert(newTask);
			i++;
		}
		if (result)
			currentSize++;
		return result;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

ScheduleMethod* MultiLevelQueue::operator[](int index) {
	return queues[index];
}

ScheduleMethod* MultiLevelQueue::operator[](eType type) {
	ScheduleMethod* queuePtr = queues[0];
	while (queuePtr)
	{
		if (queuePtr->getType() == type)
			return queuePtr;
		queuePtr++;
	}
	return nullptr;
}

MultiLevelQueue& MultiLevelQueue::getMLQ(int maxCapacity = 100
	                   , int PriorityLimitTasksToExec = 10, int PriorityCloseToStarvation = 10
	                   , int FCFSlimitTasksToExec =7, int FCFScloseToStarvation=15)
{
	static MultiLevelQueue MLQ(maxCapacity ,PriorityLimitTasksToExec,PriorityCloseToStarvation,FCFSlimitTasksToExec,FCFScloseToStarvation);
	return MLQ;
}
