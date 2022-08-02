#include "Task.h"

bool operator<(const Task& task1, const Task& task2)
{
    if (task1.getPriority() == task2.getPriority())
        return task1.getArriavlTime() < task2.getArriavlTime();
    return task1.getPriority() < task2.getPriority();
}

bool operator>(const Task& task1, const Task& task2)
{
    if (task1.getPriority() == task2.getPriority())
        return task1.getArriavlTime() > task2.getArriavlTime();
    return task1.getPriority() > task2.getPriority();
}

Task::Task(int taskId, int type, int (*func)(void*),
    int arriavlTime, int priority, void* args)
{
    this->taskId = taskId;
    this->type = (Task::eType)type;
    this->func = *func;
    this->arriavlTime = arriavlTime;
    this->priority = priority;
    this->args = args;
}


bool Task::Start()
{
    func(args);
    return true;
}
