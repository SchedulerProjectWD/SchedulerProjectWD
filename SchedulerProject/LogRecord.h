#pragma once
#include <iostream>
#include <string.h>
#include "Timer.h"
#include "constDefinitions.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

const int MESSAGE_SIZE = 50;

enum LogType
{
	INFO = 1,
	WARNING = 2,
	ERROR = 4,
	TASK = 8,
	SCHEDULER = 16,
	MLQ = 32
};

struct LogRecord
{
	LogType type;
	int time;
	//for message about tasks
	int taskId;
	int arrivalTime;
	int timeOut;
	char message[MESSAGE_SIZE];

	LogRecord()
		:type(INFO), taskId(0), message(""), time(0)
	{ }

	LogRecord(LogType type, const char* message,
		int taskId = DEFAULT_VALUE,
		int arrivalTime = DEFAULT_VALUE, int timeOut = DEFAULT_VALUE) :
		type(type), time(Timer::GetTime()),
		taskId(taskId), arrivalTime(arrivalTime) , timeOut(DEFAULT_VALUE)
	{
		strcpy_s((char*)this->message, strlen(message) + 1, message);
	}
};
