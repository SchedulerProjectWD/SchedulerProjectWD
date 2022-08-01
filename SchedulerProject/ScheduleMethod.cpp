#include "ScheduleMethod.h"

inline ScheduleMethod::ScheduleMethod(int limitTasks):limitTasksToExec(limitTasks)
,doneTasks(0)
{
}

inline int ScheduleMethod::getLimitTasks() const
{
	return limitTasksToExec;
}

inline int ScheduleMethod::getDoneTasks()
{
	return doneTasks;
}

inline void ScheduleMethod::IncreaseDoneTasks()
{
	doneTasks++;
}

inline void ScheduleMethod::ResetDoneTasks()
{
	doneTasks = 0;
}
