#include "ScheduleMethod.h"
#pragma once
#ifndef _TASK_H_
#define _TASK_H_


class Task
{
public:
	Task(int taskId, eType type, int (*func)(void*),
		int arriavlTime, int priority = 0, void* args = nullptr);

	eType getType()		 const { return eType(this->type); }
	int getTaskId()		 const { return this->taskId; }
	auto getFunc()		 const { return this->func; }
	int getArriavlTime() const { return this->arriavlTime; }
	int getPriority()	 const { return this->priority; }
	int getTimeOut() { return timeOut; }
	void setPriority(const int newPriority) { this->priority = newPriority; };
	bool Start();
	friend bool operator<(const Task& task1, const Task& task2);
	friend bool operator>(const Task& task1, const Task& task2);
	friend bool operator>(const Task& task, const int priotity);
	friend bool operator<(const Task& task, const int priotity);
	void operator=(int priority);
private:
	void* args;
	int taskId;
	eType type;
	int (*func)(void*);
	int arriavlTime;
	int priority;
	int timeOut;
};

#endif // !_TASK_H_


