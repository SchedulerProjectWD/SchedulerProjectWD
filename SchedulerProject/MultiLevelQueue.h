#pragma once
#include "ScheduleMethod.h"
#include "Task.h"

class MultiLevelQueue {
private:
	ScheduleMethod** queues;
	int currentSize;
	int maxCapacity;
	const int QUEUES_COUNT = 3;
	const int CLOSE_TO_STARVATION_HIGH = 3;
	const int CLOSE_TO_STARVATION_LOW = 3;
	const int CLOSE_TO_STARVATION_RT = 3;
	MultiLevelQueue(int maxCapacity);

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
