#include "ScheduleMethod.h"
#include "Task.h"

class MultiLevelQueue {
private:
	ScheduleMethod** queues;
	int currentSize;
	const int maxCapacity;
	const int queuesCount = 3;
	MultiLevelQueue(int maxCapacity);
public:
	int getCurrentSize();
	int getMaxCapacity();
	bool IsEmpty();
	bool IsFull();
	void decreaseCurrentSize();
	bool AddNewTask(Task* newTask);
	ScheduleMethod* operator[](int index);
	ScheduleMethod* operator[](eType type);
	static MultiLevelQueue& getMLQ(int maxCapacity);
};

