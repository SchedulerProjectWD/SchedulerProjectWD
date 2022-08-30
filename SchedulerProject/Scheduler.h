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
	void log(const char* message, LogType type = INFO);
public:
	int SystemActivation(std::condition_variable* CVisThereWaitingTask);
	Scheduler();
	~Scheduler();
	Logger* getLogger() const;
};
