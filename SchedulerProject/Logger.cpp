#pragma once
#include "Logger.h"
#include "LogRecord.h"
#include "constDefinitions.h"
#include <string>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

Logger::Logger(const char* path, const char* historyFilePath) 
	:positionRead(0), countWrite(0), path(path), pathHistoryFile(historyFilePath) {}

Logger::~Logger()
{
	LogRecord record;
	string strRecord;
	ofstream logFile(pathHistoryFile, ios::in | ios::out | ios::app);
	if (!logFile)
		throw exception("could not open file");

	//get the current time and write in the history log
	time_t now = time(0);
	char currentTime[26] = {};
	ctime_s(currentTime, 26, &now);
	logFile << currentTime;
	positionRead = 0;
	for (int i = 0; i < GetLength(); i++)
	{
		*this >> record;
		++(*this);
		strRecord = "time: " + to_string(record.time) +
			"; message: " + record.message + ";";
		if (record.type == TASK)
		{
			strRecord += " taskId: " + to_string(record.taskId) + "; arrivalTime: " + to_string(record.arrivalTime)
				+ "; timeOut: " + to_string(record.timeOut) + ";";
		}
		strRecord += "\n";
		logFile << strRecord;
	}
	remove("log.bin");
	fileStream.close();
}

int Logger::GetLength()
{
	return countWrite;
}

Logger& Logger::operator<<(const LogRecord& record)
{
	fileStream.open(path, ios::out | ios::app | ios::binary);
	if (!fileStream) {
		//to create the file in the first time:
		fileStream.open(path, ios::out | ios::app | ios::binary);
		if (!fileStream)
			throw exception("could not open file");
	}
	fileStream.write((char*)&record, sizeof(record));
	fileStream.close();
	countWrite++;
	return *this;
}

Logger& Logger::operator>>(LogRecord& record)
{
	fileStream.open(path, ios::in | ios::binary);
	if (!fileStream)
		throw exception("could not open file");
	fileStream.seekg(positionRead * sizeof(LogRecord), ios::beg);
	fileStream.read((char*)&record, sizeof(LogRecord));
	fileStream.close();
	return *this;
}

LogRecord& Logger::operator[](int index)
{
	fileStream.open(path, ios::in | ios::binary);
	if (!fileStream)
		throw exception("could not open file");
	fileStream.seekg(index * sizeof(LogRecord), ios::beg);
	fileStream.read((char*)&readRecord, sizeof(readRecord));
	fileStream.close();
	return readRecord;
}

//prefix
Logger& Logger::operator++()
{
	if (positionRead == GetLength())
		positionRead = 0;
	else
		positionRead++;
	return *this;
}

bool Logger::operator!()
{
	return !fileStream;
}

