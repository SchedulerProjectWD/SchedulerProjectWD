#pragma once
#include "pch.h"

#include "../SchedulerProject/MultiLevelQueue.cpp"
#include "../SchedulerProject/ScheduleMethod.cpp"
#include "../SchedulerProject/PrioritySchedule.cpp"
#include "../SchedulerProject/Scheduler.cpp"
#include "../SchedulerProject/UI.cpp"
#include <condition_variable>

int UI::autoId = 0;
#pragma region Insert

const int NUM_TASKS = 6;

int demoFuncRTInsert(void*) {
	return 1;
}

class InsertRTTest :public testing::Test
{
protected:
	Task* arrTasks[NUM_TASKS] = {
		new Task(1, (int)eType::real_time, demoFuncRTInsert, 1, CLOSE_TO_STARVATION_RT, 50, nullptr),
		new Task(2, (int)eType::real_time, demoFuncRTInsert, 1, CLOSE_TO_STARVATION_RT, 0, nullptr),
		new Task(3, (int)eType::real_time, demoFuncRTInsert, 2, CLOSE_TO_STARVATION_RT, 50, nullptr),
		new Task(4, (int)eType::real_time, demoFuncRTInsert, 2, CLOSE_TO_STARVATION_RT, MAX_TASK_PRIORITY, nullptr),
		new Task(5, (int)eType::real_time, demoFuncRTInsert, 3, CLOSE_TO_STARVATION_RT, 50, nullptr),
		new Task(6, (int)eType::real_time, demoFuncRTInsert, 3, CLOSE_TO_STARVATION_RT, 0, nullptr),
	};
	Scheduler scheduler;
	int expected[NUM_TASKS] = { 4,1,3,5,2,6 };
	int result[NUM_TASKS] = { 0, 0, 0, 0, 0, 0 };
	LogRecord record;
	bool flag = true;
public:
	~InsertRTTest()
	{
		for (int i = 0; i < NUM_TASKS; i++)
		{
			delete arrTasks[i];
		}
	}
};

TEST_F(InsertRTTest, Read)
{
	for (int i = 0; i < NUM_TASKS; i++)
	{
		MultiLevelQueue::getMLQ().AddNewTask(arrTasks[i]);
	}
	MultiLevelQueue::getMLQ().isActive = false;
	scheduler.SystemActivation(&CVisThereWaitingTask);
	Logger* schedulerLogger = scheduler.getLogger();
	int length = schedulerLogger->GetLength();
	for (int i = 0; i < length; i++)
	{
		record = (*schedulerLogger)[i];
		if (record.type == TASK)
			result[i] = record.taskId;
	}
	for (int i = 0; i < NUM_TASKS; i++)
	{
		if (result[i] != expected[i])
			flag = false;
	}
	EXPECT_EQ(flag, true);
}
#pragma endregion

#pragma region Read Write

int x = -1;
int updateX(void*)
{
	x = 1;
	return x;
}
int readX(void*)
{
	std::cout << x;
	return x;
}

class ReadWriteTest :public testing::Test {
protected:
	Task* writePriorityScheduling = new Task(1, (int)eType::real_time, updateX, 1, 0, 10, nullptr);
	Task* readPriorityScheduling = new Task(2, (int)eType::real_time, readX, 1, 0, 5, nullptr);
	Task* writeTimeSchedulig = new Task(1, (int)eType::real_time, updateX, 1, 0, 10, nullptr);
	Task* readTimeScheduling = new Task(2, (int)eType::real_time, readX, 2, 0, 10, nullptr);
};

TEST_F(ReadWriteTest, checkPriorityScheduling)
{
	MultiLevelQueue::getMLQ().AddNewTask(readPriorityScheduling);
	MultiLevelQueue::getMLQ().AddNewTask(writePriorityScheduling);
	MultiLevelQueue::getMLQ().isActive = false;

	Scheduler scheduler;

	testing::internal::CaptureStdout();
	scheduler.SystemActivation(&CVisThereWaitingTask);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "1");
}

TEST_F(ReadWriteTest, checkArrivalTime)
{
	MultiLevelQueue::getMLQ().AddNewTask(readTimeScheduling);
	MultiLevelQueue::getMLQ().AddNewTask(writeTimeSchedulig);
	MultiLevelQueue::getMLQ().isActive = false;

	Scheduler scheduler;

	testing::internal::CaptureStdout();
	scheduler.SystemActivation(&CVisThereWaitingTask);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "1");
}
#pragma endregion

#pragma region Starvation
class StarvationRTUnitTest :public testing::Test
{
public:
	Task* taskWithHIghPriorit = new Task(1, (int)eType::real_time, demoFuncRTInsert, 0, DEFAULT_VALUE, MAX_TASK_PRIORITY - 1, nullptr);
	Task* taskWithLowPriorit = new Task(2, (int)eType::real_time, demoFuncRTInsert, 0, DEFAULT_VALUE, 0, nullptr);
};

TEST_F(StarvationRTUnitTest, detactStarvationInRT) {
	std::thread insertThread([&] {
		UI ui;
		for (int i = 0; i < MLQ_MAX_CAPACITY - 1; i++)
		{
			Task* taskWithHIghPriority = new Task(0, 0, demoFuncRTInsert, i, DEFAULT_VALUE, MAX_TASK_PRIORITY, nullptr);
			ui.sendTaskToMLQ(taskWithHIghPriority, &CVisThereWaitingTask);
		}
		ui.sendTaskToMLQ(taskWithLowPriorit, &CVisThereWaitingTask);
		MultiLevelQueue::getMLQ().isActive = false;
	});

	Scheduler scheduler;
	scheduler.SystemActivation(&CVisThereWaitingTask);
	insertThread.join();
	int count = scheduler.getLogger()->GetLength();
	bool isThereTaskWithLongWaitingTime = false;
	for (int i = count - 1; i > 0; i--)
	{
		LogRecord r = (*scheduler.getLogger())[i];
		if (((r.time - r.arrivalTime) > WAITING_TIME_LIMIT_RT))
			isThereTaskWithLongWaitingTime = true;
	}
	EXPECT_EQ(isThereTaskWithLongWaitingTime, false);
}
#pragma endregion
