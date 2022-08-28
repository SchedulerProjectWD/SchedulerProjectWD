#include "FCFSSchedule.h"
#include "Node.h"
#include "Timer.h"
#include <climits>

FCFSSchedule::FCFSSchedule(int limitTasksToExec, int closeToStarvation, eType type)
	:ScheduleMethod(limitTasksToExec, closeToStarvation, type)
{
	queue = new Queue<Task>();
}

FCFSSchedule::~FCFSSchedule()
{
	delete queue;
}

bool FCFSSchedule::Insert(Task* task)
{
	queue->enqueue(task);
	return true;
}

Task* FCFSSchedule::ScheduleTask()
{
	return queue->dequeue();
}

bool FCFSSchedule::IsEmpty()
{
	return queue->is_empty();
}

int FCFSSchedule::GetNumWaitingTasks()
{
	return queue->getSize();
}

//Function that returns smallest Remaining Time Till Timeout
// from the queue.
Node<Task>* FCFSSchedule::smallestRemainingTimeTillTimeout(Node<Task>* head, int curentTime)
{
	Node<Task>* minTaskDetected = nullptr;
	int minTimeDetected = INT_MAX;
	int tasksWaitingTime;
	int remainTimeTillTimeout;

	while (head != nullptr) {
		tasksWaitingTime = curentTime - head->data->getArriavlTime();
		remainTimeTillTimeout = head->data->getTimeOut() - tasksWaitingTime;
		if (remainTimeTillTimeout < minTimeDetected && remainTimeTillTimeout <= closeToStarvation)
		{
			minTaskDetected = head;
			minTimeDetected = remainTimeTillTimeout;
		}
		head = head->next;
	}
	return minTaskDetected;
}

// Function that returns a list of size limit containing close-to-timeout
// tasks that where removed from the Q.
LinkedList<Task>* FCFSSchedule::DetectSystem(int limit)
{
	if (this->IsEmpty()) return nullptr;
	int currentTime = Timer::GetTime();
	LinkedList<Task>* tasksToMoveToRT = new LinkedList<Task>();
	LinkedList<Task>* innerQ = queue->getInnerList();
	for (int detectedTasks = 0; detectedTasks < limit; detectedTasks++)
	{
		//get task close to timeOut
		Node<Task>* starvingTask = smallestRemainingTimeTillTimeout(innerQ->getHead(), currentTime);
		//no starvation detected- stop searching even though it didnt reach limit
		if (starvingTask == nullptr) break;
		//if a close-to-timeout task detected, add to the detected list
		tasksToMoveToRT->addToBack(starvingTask->data);
		//delet the detected task from the Q- it passes now to deffrent DS
		innerQ->deleteNode(starvingTask);
	}
	return tasksToMoveToRT;
}