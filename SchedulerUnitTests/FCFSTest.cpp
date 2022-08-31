#pragma once
#include "pch.h"
#include "../SchedulerProject/FCFSSchedule.cpp"

TEST(QueuesTest, insertion) {
	int autoId = 0;
	FCFSSchedule highQueue(10, 10, eType::high);
	for (int i = 0; i < 10; i++)
	{
		Task* task = new Task(autoId++, (int)eType::high, nullptr, i, 10, 0, nullptr);
		highQueue.Insert(task);
	}
	for (int i = 0; i < 10; i++) {
		Task* t = highQueue.ScheduleTask();
		EXPECT_EQ(t->getTaskId(), i);
		delete t;
	}
}