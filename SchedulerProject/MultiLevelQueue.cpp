#include "MultiLevelQueue.h"
#include "FCFSSchedule.h"
#include <exception>

MultiLevelQueue::MultiLevelQueue(int maxCapacity) :maxCapacity(maxCapacity) {
	queues = new ScheduleMethod * [queuesCount];
	currentSize = 0;
	for (int i = 0; i < queuesCount; i++)
	{
		queues[i] = nullptr;
	}
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

MultiLevelQueue& MultiLevelQueue::getMLQ(int maxCapacity) {
	static MultiLevelQueue MLQ(maxCapacity);
	return MLQ;
}
