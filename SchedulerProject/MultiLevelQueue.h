#pragma once
#include "ScheduleMethod.h"
#include "constDefinitions.h"

static std::mutex mtx;
static std::condition_variable condVar;
static bool isThereWaitingTask = false;

class MultiLevelQueue {
private:
	ScheduleMethod** queues;
	int currentSize;
	int maxCapacity;
	MultiLevelQueue(int maxCapacity);
	MultiLevelQueue() = delete;

public:
	int getCurrentSize();
	int getMaxCapacity();
	bool IsEmpty();
	bool IsFull();
	int getQueuesCount();
	void decreaseCurrentSize();
	bool AddNewTask(Task* newTask);
	ScheduleMethod* operator[](int index);
	ScheduleMethod* operator[](eType type);
	static MultiLevelQueue& getMLQ(int maxCapacity);
};
