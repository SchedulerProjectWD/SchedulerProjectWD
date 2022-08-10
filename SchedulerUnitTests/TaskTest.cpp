#include "pch.h"
#include "../SchedulerProject/Task.h"
#include "../SchedulerProject/Task.cpp"
int demoFunc(void*) {
	return 1;
}

class TaskTest : public ::testing::Test {
protected:
	void SetUp() override {

	}
	Task* RTtask1 = new Task(1, 1, demoFunc, 1, 3, 50);
	Task* RTtask2 = new Task(2, 1, demoFunc, 2, 4, 50);
	~TaskTest() {
		delete RTtask1;
		delete RTtask2;
	}
};
TEST_F(TaskTest, TestOerator){
	bool isGrater = RTtask1 < RTtask2;
	EXPECT_EQ(isGrater, false);
	bool isGrater2 = RTtask1 > RTtask2;
	EXPECT_EQ(isGrater2, true);
};