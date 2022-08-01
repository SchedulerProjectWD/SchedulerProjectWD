#pragma once
#include "Task.h"

class ScheduleMethod
{
	int limitTasksToExec;
	int doneTasks;

public:
	ScheduleMethod(int limitTasks);
	virtual Task* ScheduleTask() = 0;
	virtual bool Insert(Task* task) = 0;
	virtual bool IsEmpty() = 0;
	int getLimitTasks() const;
	int getDoneTasks();
	void IncreaseDoneTasks();
	void ResetDoneTasks();
};

