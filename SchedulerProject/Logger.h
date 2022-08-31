#pragma once
#include <fstream>
#include "LogRecord.h"

class Logger
{
	std::fstream fileStream;
	const char* path;
	const char* pathHistoryFile;
	int countWrite;
	LogRecord readRecord;

public:
	int positionRead;
	Logger(const char* path, const char* historyFilePath = "history_log.txt");
	~Logger();
	//returns how many messages have written to th logger
	int GetLength();
	Logger& operator<<(const LogRecord& record);
	Logger& operator>>(LogRecord& record);
	LogRecord& operator[](int index);
	Logger& operator++();
	bool operator!();
};

