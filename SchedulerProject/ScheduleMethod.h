#pragma once
#include "Task.h"
#include "LinkedList.h"

class ScheduleMethod
{
protected:
	int limitTasksToExec;
	int doneTasks;
	int closeToStarvation;

public:
	ScheduleMethod(int limitTasks, closeToStarvation);
	virtual Task* ScheduleTask() = 0;
	virtual bool Insert(Task* task) = 0;
	virtual bool IsEmpty() = 0;
	ScheduleMethod(int limitTasks, int closeToStarvation);
	int getLimitTasks() const;
	int getDoneTasks() const;
	int getCloseToStarvation() const;
	void IncreaseDoneTasks();
	void ResetDoneTasks();
	virtual LinkedList<Task>* detectSystem(int limit) = 0;
};
