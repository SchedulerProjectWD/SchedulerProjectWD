#include "Task.hpp"
#include "MaxHeap.h"

class PrioritySchedule
{
private:
	MaxHeap<Task>* queue;
	const int Max_Priority = 200;
	const int Close_To_Starvation = 0;
	const int Waiting_Time_Limit = 0;
public:
	PrioritySchedule(int limit_size);
	~PrioritySchedule();
	Task* scheduleTask();
	bool insert(Task* task);
	bool insertFromLowQueue(Task* task);
	void detactStarvation();
};


PrioritySchedule::PrioritySchedule(int limit_size) {
	queue = new MaxHeap<Task>(limit_size);
}

PrioritySchedule::~PrioritySchedule() {
	queue->~MaxHeap();
	delete this;
}

bool PrioritySchedule::insert(Task* task) {

	return queue->insert(task);
}

Task* PrioritySchedule::scheduleTask() {
	return queue->extractMax();
}

bool PrioritySchedule::insertFromLowQueue(Task* task) {

	Task** highestPriorityTasks = (Task**)malloc(sizeof(Task*) * 10);

	//determine what priority the task would get:
	int task_priority = Max_Priority;     //default
	for (size_t i = 0; i < 10; i++)
	{
		highestPriorityTasks[i] = queue->extractMax();
		if (highestPriorityTasks[i] && highestPriorityTasks[i]->getArrivalTime() >= Close_To_Starvation)
			task_priority = min(task_priority, highestPriorityTasks[i]->priority - 1);
	}
	for (size_t i = 0; i < 10; i++)    //put back the 10 highest priority tasks that were extracted .
		queue->insert(highestPriorityTasks[i]);

	task->priority = task_priority;
	return queue->insert(task);
}

void  PrioritySchedule::detactStarvation()
{
	detactStarvation(queue, Close_To_Starvation, Max_Priority);
}


