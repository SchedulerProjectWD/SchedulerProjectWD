#pragma once
#include <fstream>
#include "LogRecord.h"

class Logger
{
	std::fstream fileStream;
	const char* path;
	int countWrite;
	LogRecord readRecord;

public:
	int positionRead;
	Logger(const char* path);
	~Logger();
	//returns how many messages have written to th logger
	int GetLength();
	Logger& operator<<(const LogRecord& record);
	Logger& operator>>(LogRecord& record);
	LogRecord& operator[](int index);
	Logger& operator++();
	bool operator!();
};

