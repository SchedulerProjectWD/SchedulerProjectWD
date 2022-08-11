#pragma once
#include <iostream>
#include <string.h>
#include "Timer.h"
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
	char message[MESSAGE_SIZE];
	LogRecord() :type(INFO), message(""), time(0) { }
	LogRecord(LogType type, const char* message) :
		type(type), time(Timer::GetTime()) {
		strcpy_s((char*)this->message, strlen(message) + 1, message);
	}
	void setMessage(const char* message) {
		strcpy_s((char*)this->message, strlen(message) + 1, message);
	}
};
