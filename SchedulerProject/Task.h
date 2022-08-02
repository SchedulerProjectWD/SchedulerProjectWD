#pragma once
#ifndef _TASK_H_
#define _TASK_H_


class Task
{
public:
	Task(int taskId, int type, int (*func)(void*),
		int arriavlTime, int priority = 0, void* args = nullptr);
	enum eType { real_time, low, high };
	int getTaskId() const { return this->taskId; }
	eType getType() const { return this->type; }
	auto getFunc() const { return this->func; }
	int getArriavlTime() const { return this->arriavlTime; }
	int getPriority() const { return this->priority; }
	void setPriority(const int newPriority) { this->priority = newPriority; };
	friend bool operator<(const Task& task1, const Task& task2);
	friend bool operator>(const Task& task1, const Task& task2);
	bool Start();
private:
	void* args;
	int taskId;
	eType type;
	int (*func)(void*);
	int arriavlTime;
	int priority;
};
#endif // !_TASK_H_

