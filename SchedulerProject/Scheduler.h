#pragma once
#include "MultiLevelQueue.h"
#include "Logger.h"
#include "Task.h"
#include "constDefinitions.h"
#include "ScheduleMethod.h"

class Scheduler {
private:
	MultiLevelQueue* MLQ;
	Task* currentTask;
	Logger* logger;
	void newRound();
	void AvoidStarvation();
public:
	int SystemActivation();
	Scheduler();
	~Scheduler();
};
