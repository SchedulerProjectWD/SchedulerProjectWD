#pragma once

enum class eType { real_time, high, low };

class Task
{
public:
	Task(int taskId, int type, int (*func)(void*), int arriavlTime,
		int timeOut, int priority, void* args);
	eType getType()		 const { return eType(this->type); }
	int getTaskId()		 const { return this->taskId; }
	auto getFunc()		 const { return this->func; }
	int getArriavlTime() const { return this->arriavlTime; }
	int getPriority()	 const { return this->priority; }
	int getTimeOut() { return timeOut; }
	void setPriority(const int newPriority) { this->priority = newPriority; };
	bool Start();
	friend bool operator<(const Task& task1, const Task& task2);
	friend bool operator>(const Task& task1, const Task& task2);
	friend bool operator>=(const Task& task1, const Task& task2);
	bool operator>(const int otherPriotity) const;
	bool operator<( const int otherPriotity) const;
	void operator=(int priority);
private:
	void* args;
	int taskId;
	eType type;
	int (*func)(void*);
	int arriavlTime;
	int priority;
	int timeOut;
};


