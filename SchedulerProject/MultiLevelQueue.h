#pragma once
#include <atomic>
//#include <mutex>  
#include "ScheduleMethod.h"
#include "constDefinitions.h"

static std::mutex mtx;
//static std::unique_lock<std::mutex> ul(mtx, std::defer_lock);
//static std::shared_ptr<std::condition_variable> condVar = std::make_shared<std::condition_variable>();
static std::condition_variable condVar;// = std::make_shared<std::condition_variable>();
//static std::atomic_bool isThereWaitingTask(false);

class MultiLevelQueue {
private:
	ScheduleMethod** queues;
	int currentSize;
	int maxCapacity;
	MultiLevelQueue(int maxCapacity);
	MultiLevelQueue() = delete;

public:
	std::atomic_bool isActive;
	int getCurrentSize();
	int getMaxCapacity();
	bool IsEmpty();
	bool IsFull(eType type);
	int getQueuesCount();
	void decreaseCurrentSize();
	bool AddNewTask(Task* newTask);
	ScheduleMethod* operator[](int index);
	ScheduleMethod* operator[](eType type);
	static MultiLevelQueue& getMLQ(int maxCapacity=MAX_CAPACITY);
};
