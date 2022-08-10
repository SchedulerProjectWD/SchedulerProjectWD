#include "Scheduler.h"
#include "PrioritySchedule.h"
#include "Timer.h"

Scheduler::Scheduler() {
	MLQ = &(MultiLevelQueue::getMLQ(MAX_CAPACITY));
	//cout << MLQ << endl;
	//logger = new Logger("");
}

Scheduler::~Scheduler()
{
	//delete MLQ;
}

void Scheduler::AvoidStarvation() {

	for (int i = 0; i < MLQ->getQueuesCount(); i++)
	{
		LinkedList<Task>* starvedFCFSTasks=(*MLQ)[i]->DetectSystem();
		if (starvedFCFSTasks)
			((PrioritySchedule*)(*MLQ)[eType::real_time])->InsertFromAnotherQueue(starvedFCFSTasks);
	}
}

int Scheduler::SystemActivation()
{
	while (!MLQ->IsEmpty())
	{
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
				else
					continue;
		currentTask = (*MLQ)[currentType]->ScheduleTask();
		MLQ->decreaseCurrentSize();
		bool success = currentTask->Start();
		Timer::IncreaseTime();
		//use logger:
		///logRecord* record=new logRecord(currentType,success+);
		//logger << 

		if (Timer::GetTime() % TIME_TO_DETECT_SYSTEM == 0)
			AvoidStarvation();
	}
	return 0;
}