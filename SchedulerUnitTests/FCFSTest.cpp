#pragma once
#include "pch.h"
#include "../SchedulerProject/FCFSSchedule.cpp"
//#include "../SchedulerProject/MultiLevelQueue.cpp"
#include "../SchedulerProject/Scheduler.h"

int y = -1;
int updateY(void*)
{
	y = 1;
	return y;
}
int readY(void*)
{
	std::cout << y;
	return y;
}

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


TEST(ReadWriteUnitTest,HighLow)
{
	Task* writeTimeSchedulig = new Task(1, (int)eType::high, updateY, 1, 0, 10, nullptr);
	Task* readTimeScheduling = new Task(2, (int)eType::low, readY, 2, 0, 10, nullptr);

	MultiLevelQueue::getMLQ().AddNewTask(readTimeScheduling);
	MultiLevelQueue::getMLQ().AddNewTask(writeTimeSchedulig);
	MultiLevelQueue::getMLQ().isActive = false;

	Scheduler scheduler;

	testing::internal::CaptureStdout();
	scheduler.SystemActivation(&CVisThereWaitingTask);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "1");
}
