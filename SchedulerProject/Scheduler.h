#include "MultiLevelQueue.h"
#include "Logger.h"
#include "Task.h"
const int MAX_CAPACITY = 200;
const int TIME_TO_DETECT_SYSTEM = 20;

class Scheduler {
private:
	MultiLevelQueue* MLQ;
	Task* currentTask;
	//Logger* logger;
	void newRound();
	void AvoidStarvation();
public:
	int SystemActivation();
	Scheduler();
	~Scheduler();
};
