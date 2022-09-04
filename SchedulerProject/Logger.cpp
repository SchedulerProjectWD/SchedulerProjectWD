#pragma once
#include "Logger.h"
#include "LogRecord.h"
#include "constDefinitions.h"
#include <string>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

//std::mutex Logger::mtx;
//std::condition_variable Logger::CVisFileOpen;

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
			"; message: " + record.message + 
			"; taskId: " + to_string(record.taskId) + 
			"; arrivalTime: " + to_string(record.arrivalTime)+ 
			"; timeOut: " + to_string(record.timeOut) + ";\n";
		logFile << strRecord;
	}
	remove(path);
	fileStream.close();
}

int Logger::GetLength()
{
	return countWrite;
}

Logger& Logger::operator<<(const LogRecord& record)
{
	//while (fileStream.is_open());
	void* x = &mtx;
	std::unique_lock<std::mutex> ul(mtx);
	CVisFileOpen.wait(ul, [&] {return !fileStream.is_open(); });
	fileStream.open(path, ios::out | ios::app | ios::binary);
	if (!fileStream) {
		//to create the file in the first time:
		fileStream.open(path, ios::out | ios::binary);
		if (!fileStream)
			throw exception("could not open file");
	}
	fileStream.write((char*)&record, sizeof(record));
	fileStream.close();
	CVisFileOpen.wait(ul, [&] {return !fileStream.is_open(); });
	ul.unlock();
	countWrite++;
	return *this;
}

Logger& Logger::operator>>(LogRecord& record)
{
	//while (fileStream.is_open());
	void* x = &mtx;

	std::unique_lock<std::mutex> ul(mtx);
	CVisFileOpen.wait(ul, [&] {return !fileStream.is_open(); });
	fileStream.open(path, ios::in | ios::binary);
	if (!fileStream)
		throw exception("could not open file");
	fileStream.seekg(positionRead * sizeof(LogRecord), ios::beg);
	fileStream.read((char*)&record, sizeof(LogRecord));
	fileStream.close();
	CVisFileOpen.notify_all();
	ul.unlock();
	return *this;
}

LogRecord& Logger::operator[](int index)
{
	//while (fileStream.is_open());
	std::unique_lock<std::mutex> ul(mtx);
	CVisFileOpen.wait(ul, [&] {return !fileStream.is_open(); });
	fileStream.open(path, ios::in | ios::binary);
	if (!fileStream)
		throw exception("could not open file");
	fileStream.seekg(index * sizeof(LogRecord), ios::beg);
	fileStream.read((char*)&readRecord, sizeof(readRecord));
	fileStream.close();
	CVisFileOpen.notify_all();
	ul.unlock();
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

