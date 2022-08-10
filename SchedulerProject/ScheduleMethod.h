#pragma once
#include "Task.h"
#include "LinkedList.h"

class ScheduleMethod
{
protected:
	int limitTasksToExec;
	int doneTasks;
	int closeToStarvation;
	eType type;
public:
	ScheduleMethod(int limitTasksToExec, int closeToStarvation, eType type);
	eType getType() const;
	int getLimitTasksToExec() const;
	int getDoneTasks() const;
	int getCloseToStarvation() const;
	void IncreaseDoneTasks();
	void ResetDoneTasks();
	virtual Task* ScheduleTask() = 0;
	virtual bool Insert(Task* task) = 0;
	virtual bool IsEmpty() = 0;
	virtual int GetNumWaitingTasks() = 0;
	virtual LinkedList<Task>* DetectSystem(int limit = 0) = 0;
};
