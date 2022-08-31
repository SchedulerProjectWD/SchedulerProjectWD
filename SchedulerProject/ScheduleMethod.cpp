#pragma once
#include "ScheduleMethod.h" 

ScheduleMethod::ScheduleMethod(int limitTasksToExec, int closeToStarvation, eType type) :
	limitTasksToExec(limitTasksToExec)
	, closeToStarvation(closeToStarvation), doneTasks(0), type(type)
{
}

eType ScheduleMethod::getType() const
{
	return (eType)type;
}

int ScheduleMethod::getLimitTasksToExec() const
{
	return limitTasksToExec;
}

int ScheduleMethod::getDoneTasks() const
{
	return doneTasks;
}

int ScheduleMethod::getCloseToStarvation() const
{
	return closeToStarvation;
}

void ScheduleMethod::IncreaseDoneTasks()
{
	doneTasks++;
}

void ScheduleMethod::ResetDoneTasks()
{
	doneTasks = 0;
}
