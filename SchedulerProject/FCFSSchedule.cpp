#include "FCFSSchedule.h"
#include "Node.h"
#include <climits>

FCFSSchedule::FCFSSchedule(int limitTasks, int closeToStarvation)
	:ScheduleMethod(limitTasks, closeToStarvation)
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

// Function that returns smallest Remaining Time Till Timeout
// from the queue.
Node<Task>* FCFSSchedule::smallestRemainingTimeTillTimeout(Node<Task>* head, int curentTime)
{
	// Declare a min variable and initialize
	// it with the head
	Node<Task>* min = nullptr;
	int minCloseToTimeOut = INT_MAX;
	int waitingTime;
	int remainTimeTillTimeout;

	while (head != nullptr) {
		waitingTime = curentTime - head->data->getArriavlTime();
		remainTimeTillTimeout = head->data->getTimeOut() - waitingTime;

		if (remainTimeTillTimeout < minCloseToTimeOut && remainTimeTillTimeout <= closeToStarvation)
		{
			min = head;
			minCloseToTimeOut = remainTimeTillTimeout;
		}
		head = head->next;
	}
	return min;
}

// Function that returns a list of size limit containing close-to-timeout
// tasks that where removed from the Q.
LinkedList<Task>* FCFSSchedule::DetectSystem(int limit)
{
	if (this->IsEmpty()) return nullptr;
	int currentTime = 0;//Timer::currentTime();
	LinkedList<Task>* tasksCloseToTimeout = new LinkedList<Task>();
	LinkedList<Task>* Q = queue->getInnerList();
	for (int i = 0; i < limit; i++)
	{
		Node<Task>* currSmallest = smallestRemainingTimeTillTimeout(Q->getHead(), currentTime);
		//no starvation detected- stop searching even though it didnt reach limit
		if (currSmallest == nullptr) break;
		//if a close-to-timeout task detected, add to the detected list
		tasksCloseToTimeout->addToBack(currSmallest->data);
		//delet the detected task from the Q- it passes now to deffrent DS
		Q->deleteNode(currSmallest);
	}
	return tasksCloseToTimeout;
}