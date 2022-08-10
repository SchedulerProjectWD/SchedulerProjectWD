#include "pch.h"
#include "../SchedulerProject/Timer.h"

int Timer::time = 0;
TEST(TimerTest, InitializeWithZiro)
{
	EXPECT_EQ(Timer::GetTime(), 0);
}
TEST(TimerTest, TimerWorkes)
{
	Timer::IncreaseTime();
	EXPECT_EQ(Timer::GetTime(), 1);
	Timer::IncreaseTime();
	EXPECT_EQ(Timer::GetTime(), 2);
	Timer::IncreaseTime();
	EXPECT_EQ(Timer::GetTime(), 3);
}