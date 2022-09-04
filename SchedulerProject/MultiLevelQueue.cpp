#pragma once
#include "MultiLevelQueue.h"
#include "FCFSSchedule.h"
#include "PrioritySchedule.h"
#include <exception>

MultiLevelQueue MultiLevelQueue::MLQ(MLQ_MAX_CAPACITY);

MultiLevelQueue::MultiLevelQueue(int maxCapacity)
	:maxCapacity(maxCapacity), currentSize(0)
{
	isActive = true;
	queues = new ScheduleMethod * [QUEUES_COUNT];
	queues[0] = new PrioritySchedule(maxCapacity / 2, maxCapacity, CLOSE_TO_STARVATION_RT);
	queues[1] = new FCFSSchedule(maxCapacity / 4, CLOSE_TO_STARVATION_HIGH, eType::high);
	queues[2] = new FCFSSchedule(maxCapacity / 5, CLOSE_TO_STARVATION_LOW, eType::low);
	logger = new Logger(R"(..\logs\log.bin)");
}

bool MultiLevelQueue::IsEmpty() {
	return currentSize <= 0;
}

bool MultiLevelQueue::IsFull(eType type) {
	if (type == eType::real_time)
		return currentSize == maxCapacity;
	//to prevent inversion , - saved space to real time tasks
	return currentSize == maxCapacity - RESERVED_SPACE_TO_RT_TASKS;
}

int MultiLevelQueue::getMaxCapacity() {
	return maxCapacity;
}

Logger* MultiLevelQueue::getLogger()
{
	return logger;
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
		LogRecord record("insert new task to the MLQ", LogType::MLQ, newTask->getTaskId()
			, newTask->getArriavlTime(), newTask->getTimeOut());
		(*logger) << record;
		return result;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

int MultiLevelQueue::getQueuesCount() {
	return QUEUES_COUNT;
}

ScheduleMethod* MultiLevelQueue:: operator[](int index) {
	return queues[index];
}

ScheduleMethod* MultiLevelQueue::operator[](eType type) {
	for (int i = 0; i < QUEUES_COUNT; i++)
	{
		if (queues[i]->getType() == type)
			return queues[i];
	}
	return nullptr;
}


MultiLevelQueue& MultiLevelQueue::getMLQ()
{
	return MLQ;
}

