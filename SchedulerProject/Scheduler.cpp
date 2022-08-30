#include "Scheduler.h"
#include "PrioritySchedule.h"
#include "Timer.h"
#include <chrono>
#include <functional>

Scheduler::Scheduler() :currentTask(nullptr) {
	MLQ = &(MultiLevelQueue::getMLQ());
	logger = new Logger(R"(C:\Users\שניידר\Documents\תכנות\תשפב\Bootcamp\ProjectWD\30\log.bin)");
}

Scheduler::~Scheduler()
{
	delete logger;
}

Logger* Scheduler::getLogger() const
{
	return this->logger;
}

void Scheduler::newRound() {
	for (int i = 0; i < MLQ->getQueuesCount(); i++)
	{
		(*MLQ)[i]->ResetDoneTasks();
	}
}

void Scheduler::AvoidStarvation() {

	for (int level = 0; level < MLQ->getQueuesCount(); level++)
	{
		LinkedList<Task>* starvedFCFSTasks = (*MLQ)[level]->DetectSystem();
		if (starvedFCFSTasks)                      ///move task
			((PrioritySchedule*)(*MLQ)[eType::real_time])->InsertFromAnotherQueue(starvedFCFSTasks);
	}
}

void Scheduler::log(const char* message, LogType type)
{
	LogRecord logMessage(message, type,
		currentTask->getTaskId(), currentTask->getArriavlTime(), currentTask->getTimeOut());
	*logger << logMessage;
}

int Scheduler::SystemActivation(std::condition_variable* CVisThereWaitingTask)
{
	while (MLQ->isActive || !MLQ->IsEmpty())
	{
		std::unique_lock<std::mutex> ul(mtx);
		(*CVisThereWaitingTask).wait(ul, [this] {return !MLQ->IsEmpty() || !MLQ->isActive; });
		///choose a not empty queue with the highest weight 
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
				if (!((*MLQ)[eType::low]->IsEmpty()) && //get current weight  
					(*MLQ)[eType::low]->getDoneTasks() <= (*MLQ)[eType::low]->getLimitTasksToExec())
				{
					currentType = eType::low;
				}
				else {
					newRound();
					ul.unlock();
					continue;
				}
		//schedule a task from the chosen queue
		//LogRecord logSchduledType("scheduling a task");
		currentTask = (*MLQ)[currentType]->ScheduleTask();
		MLQ->decreaseCurrentSize();
		ul.unlock();
		CVisThereWaitingTask->notify_all();
		bool success = currentTask->Start();
		Timer::IncreaseTime();
		(*MLQ)[currentType]->IncreaseDoneTasks();

		if (success)
			log("the task got executed successfuly", TASK);
		else
			log("failed to execute task", ERR);


		if (Timer::GetTime() % TIME_TO_DETECT_SYSTEM == 0)
			AvoidStarvation();
	}
	std::cout << "exit from loop" << std::endl;
	return 0;
}
