#include "Task.h"
#include "ScheduleMethod.h"

Task::Task(int taskId, eType type, int (*func)(void*), int arriavlTime, int priority, void* args) {
    this->taskId = taskId;
    this->type = (eType)type;
    this->func = *func;
    this->arriavlTime = arriavlTime;
    this->priority = priority;
    this->args = args;
}

bool operator<(const Task& task1, const Task& task2)
{
    if (task1.priority == task2.priority)
        return task1.arriavlTime < task2.arriavlTime;
    return task1.priority < task2.priority;
}

bool operator>(const Task& task1, const Task& task2)
{
    if (task1.priority == task2.priority)
        return task1.arriavlTime > task2.arriavlTime;
    return task1.priority > task2.priority;
}

bool operator>(const Task& task, const int priority)
{
    return task.priority > priority;
}

bool operator<(const Task& task, const int priority)
{
    return task.priority < priority;
}


void Task::operator=(int priority)
{
    this->setPriority(priority);
}

bool Task::Start()
{
    func(args);
    return true;
}

 