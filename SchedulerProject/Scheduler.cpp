#include "Scheduler.h"
#include "PrioritySchedule.h"
#include "Timer.h"
#include "constDefinitions.h"

Scheduler::Scheduler() :currentTask(nullptr) {
	MLQ = &(MultiLevelQueue::getMLQ(MAX_CAPACITY));
	logger = new Logger("log.bin");
}

Scheduler::~Scheduler()
{
	delete logger;
}

void Scheduler::newRound() {
	for (int i = 0; i < MLQ->getQueuesCount(); i++)
	{
		(*MLQ)[i]->ResetDoneTasks();
	}
}

void Scheduler::AvoidStarvation() {

	for (int i = 0; i < MLQ->getQueuesCount(); i++)
	{
		LinkedList<Task>* starvedFCFSTasks = (*MLQ)[i]->DetectSystem();
		if (starvedFCFSTasks)
			((PrioritySchedule*)(*MLQ)[eType::real_time])->InsertFromAnotherQueue(starvedFCFSTasks);
	}
}

int Scheduler::SystemActivation()
{
	while (true)
	{
		///choose a not empty queue with the highest weight 
		if (MLQ->IsEmpty())
			break;//lock with CV
		eType currentType;
		if (!((*MLQ)[eType::real_time]->IsEmpty()) &&
			(*MLQ)[eType::real_time]->getDoneTasks() <= (*MLQ)[eType::real_time]->getLimitTasksToExec())
		{
			currentType = eType::real_time;
		}
		else
			if (!((*MLQ)[eType::high]->IsEmpty()) &&
				(*MLQ)[eType::high]->getDoneTasks() <= (*MLQ)[eType::high]->getLimitTasksToExec())
			{
				currentType = eType::high;
			}
			else
				if (!((*MLQ)[eType::low]->IsEmpty()) &&
					(*MLQ)[eType::low]->getDoneTasks() <= (*MLQ)[eType::low]->getLimitTasksToExec())
				{
					currentType = eType::low;
				}
				else {
					newRound();
					continue;
				}

		//schedule a task from the chosen queue
		currentTask = (*MLQ)[currentType]->ScheduleTask();
		MLQ->decreaseCurrentSize();
		//if(currentTask)
		bool success = currentTask->Start();
		Timer::IncreaseTime();
		(*MLQ)[currentType]->IncreaseDoneTasks();
		LogRecord logMessage(INFO, "thw task got executed successfuly", 
			currentTask->getTaskId(),currentTask->getArriavlTime(),currentTask->getTimeOut());
		*logger << logMessage;
		//use logger: -> the message is according success value...
		//if (success)
			//logMessage.type = (int)(TASK | INFO);

		if (Timer::GetTime() % TIME_TO_DETECT_SYSTEM == 0)
			AvoidStarvation();
	}
	return 0;
}