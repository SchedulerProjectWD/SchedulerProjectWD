#include "ScheduleMethod.h"

ScheduleMethod::ScheduleMethod(int limitTasks, int closeToStarvation) :
	limitTasksToExec(limitTasks)
	, closeToStarvation(closeToStarvation), doneTasks(0)
{
}

inline int ScheduleMethod::getLimitTasks() const
{
	return limitTasksToExec;
}

inline int ScheduleMethod::getDoneTasks() const
{
	return doneTasks;
}

inline int ScheduleMethod::getCloseToStarvation() const
{
	return closeToStarvation;
}

inline void ScheduleMethod::IncreaseDoneTasks()
{
	doneTasks++;
}

inline void ScheduleMethod::ResetDoneTasks()
{
	doneTasks = 0;
}
