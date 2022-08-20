#include "pch.h"
#include "../SchedulerProject/Logger.h"
#include "../SchedulerProject/Logger.cpp"

class LoggerTest :public testing::Test
{
protected:
	LogRecord record;
};

TEST_F(LoggerTest, Read)
{
	Logger logger("test.bin");
	logger << record;
	EXPECT_EQ(logger.GetLength(), 1);
}