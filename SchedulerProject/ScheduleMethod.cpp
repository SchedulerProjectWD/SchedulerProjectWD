#include "ScheduleMethod.h" 

ScheduleMethod::ScheduleMethod(int limitTasksToExec, int closeToStarvation) :
	limitTasksToExec(limitTasksToExec)
	, closeToStarvation(closeToStarvation), doneTasks(0)
{
}
inline eType ScheduleMethod::getType() const
{
	return (eType)type;
}
inline int ScheduleMethod::getLimitTasksToExec() const
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

 