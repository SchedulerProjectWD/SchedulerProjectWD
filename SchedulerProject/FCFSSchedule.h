#pragma once
#include "ScheduleMethod.h"
#include "Queue.h"
#include "Task.h"
class FCFSSchedule :public ScheduleMethod
{
private:
	Queue<Task>* queue;
	Node<Task>* smallestRemainingTimeTillTimeout(Node<Task>* head, int curentTime);
public:
	FCFSSchedule(int limitTasksToExec, int closeToStarvation, eType type);
	~FCFSSchedule();
	bool IsEmpty() override;
	bool Insert(Task* task) override;
	Task* ScheduleTask() override;
	LinkedList<Task>* DetectSystem(int limit = 0) override;
	int GetNumWaitingTasks() override;
};
