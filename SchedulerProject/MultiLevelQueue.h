#include "ScheduleMethod.h"
#include "Task.h"

class MultiLevelQueue {
private:
	ScheduleMethod** queues;
	int currentSize;
	const int maxCapacity;
	const int queuesCount = 3;
	MultiLevelQueue(int maxCapacity,
		//parameters for the priority scheduler :
		int PriorityLimitTasksToExec, int PriorityCloseToStarvation,
		//parameters for the FCFS scheduler :
		int FCFSlimitTasksToExec, int FCFScloseToStarvation);
public:
	int getCurrentSize();
	int getMaxCapacity();
	bool IsEmpty();
	bool IsFull();
	void decreaseCurrentSize();
	bool AddNewTask(Task* newTask);
	ScheduleMethod* operator[](int index);
	ScheduleMethod* operator[](eType type);
	static MultiLevelQueue& getMLQ(int maxCapacity
		   ,int PriorityLimitTasksToExec, int PriorityCloseToStarvation
		   ,int FCFSlimitTasksToExec, int FCFScloseToStarvation);
};
