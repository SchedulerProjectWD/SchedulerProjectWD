#include "MultiLevelQueue.h"
#include "FCFSSchedule.h"
#include "PrioritySchedule.h"
#include "Task.h"
#include <exception>

MultiLevelQueue::MultiLevelQueue(int maxCapacity)
	:maxCapacity(maxCapacity), currentSize(0)
{
	queues = new ScheduleMethod * [QUEUES_COUNT];
	queues[0] = new PrioritySchedule(maxCapacity / 2, maxCapacity, CLOSE_TO_STARVATION_RT);
	queues[1] = new FCFSSchedule(maxCapacity / 4, CLOSE_TO_STARVATION_HIGH, eType::high);
	queues[2] = new FCFSSchedule(maxCapacity / 5, CLOSE_TO_STARVATION_LOW, eType::low);
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
		while (i < QUEUES_COUNT)
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

MultiLevelQueue& MultiLevelQueue::getMLQ(int maxCapacity = 30)
{
	static MultiLevelQueue MLQ(maxCapacity);
	return MLQ;
}
