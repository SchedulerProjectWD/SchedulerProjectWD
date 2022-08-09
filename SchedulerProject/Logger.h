#pragma once
#include <fstream>
#include "LogRecord.h"
using namespace std;

class Logger
{
	fstream fileStream;
	int positionWrite;
	int positionRead;
	//const char* path;
public:
	Logger(const char* path);
	~Logger();
	Logger& operator<<(const LogRecord& record);
	Logger& operator>>(LogRecord& record);
	bool operator!();
};

