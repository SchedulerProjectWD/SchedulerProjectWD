
#include "Task.h"
#include "ScheduleMethod.h"
#include <iostream>
using namespace std;

class PrioritySchedule :ScheduleMethod
{

private:

	MaxHeap<Task>* queue;
	const int MaxPriority = 200;
	const int CloseToStarvation = 0;
	const int WaitingTimeLimit = 0;

public:

	PrioritySchedule(int limit_size);
	~PrioritySchedule();
	bool Insert(Task* task);
	bool InsertFromLowQueue(Task* task);
	void IncreaseDoneTasks();
	void DetactStarvation();
	void ResetDoneTasks();
	void IncreaseDoneTasks();
	int getLimitTasks();
	int getDoneTasks();
};

//c-tor & d-tor
PrioritySchedule::PrioritySchedule(int limitSsize, int limitTasksToExec) {

	this->limitTasksToExec = limitTasksToExec;
	doneTasks = 0;
	queue = new MaxHeap<Task>(limitSize);
}
PrioritySchedule::~PrioritySchedule() {

	delete queue;
}

//getters & setters
int PrioritySchedule::getDoneTasks() {	return doneTasks; }
int PrioritySchedule::getLimitTasks() { return limitTasksToExec; }

//ScheduleMethod override
void PrioritySchedule::ResetDoneTasks() { doneTasks = 0; }
void PrioritySchedule::IncreaseDoneTasks() { doneTasks++; }
bool PrioritySchedule::isEmpty() { return queue->isEmpty(); }
Task* PrioritySchedule::ScheduleTask() { return queue->extractMax(); }
bool PrioritySchedule::Insert(Task* task) { return queue->insert(task); }

inline bool PrioritySchedule::InsertFromLowQueue(Task* task) {

	Task** highestPriorityTasks = (Task**)malloc(sizeof(Task*) * 10);
	//determine what priority the task would get:
	int task_priority = MaxPriority;     //default value

	for (size_t i = 0; i < 10; i++)
	{
		highestPriorityTasks[i] = queue->extractMax();
		if (highestPriorityTasks[i] && highestPriorityTasks[i]->getArriavlTime() >= CloseToStarvation)
			task_priority = min(task_priority, highestPriorityTasks[i]->getPriority() - 1);
	}
	for (size_t i = 0; i < 10; i++)    //put back the 10 highest priority tasks that were extracted .
		queue->insert(highestPriorityTasks[i]);
	task->setPriority(task_priority);
	return queue->insert(task);
}

inline void PrioritySchedule::DetactStarvation()
{
	int countTasks = queue.getSize();

	for (size_t i = 0; i < countTasks; i++)
		if (queue[i]->getArrivalTime() >= CloseToStarvation)
			queue[i]->changePriority(MaxPriority);
}

