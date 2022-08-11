#include "Logger.h"
#include "LogRecord.h"
#include "constDefinitions.h"
#include <string>
using namespace std;

Logger::Logger(const char* path) :positionRead(0), countWrite(0), path(path) {}

Logger::~Logger()
{
	LogRecord record;
	string strRecord;
	ofstream logFile("history_log.txt", ios::in | ios::out | ios::app);
	if (!logFile)
		throw exception("could not open file");
	positionRead = 0;
	for (int i = 0; i < GetLength(); i++)
	{
		*this >> record;
		++(*this);
		string mes(record.message);
		strRecord = "time: " + to_string(record.time) + "; message: " + mes.c_str() + ";\n";
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
	fileStream.read((char*)&record, sizeof(record));
	fileStream.close();
	return *this;
}

LogRecord& Logger::operator[](int index)
{
	LogRecord record;
	fileStream.open(path, ios::in | ios::binary);
	if (!fileStream)
		throw exception("could not open file");
	fileStream.seekg(index * sizeof(LogRecord), ios::beg);
	fileStream.read((char*)&record, sizeof(record));
	return record;
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
