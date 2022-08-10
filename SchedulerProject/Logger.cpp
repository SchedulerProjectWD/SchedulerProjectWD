#include "Logger.h"
#include "LogRecord.h"
#include <string>
using namespace std;

Logger::Logger(const char* path) :positionRead(0) {

	fileStream.open(path, ios::in | ios::out | ios::binary);
	if (!fileStream)
		throw exception("could not open file");
}

Logger::~Logger()
{
	LogRecord record;
	string strRecord;
	ofstream logFile("log.txt", ios::out | ios::app);
	fileStream.seekg(0, ios::beg);
	while (!fileStream.eof())
	{
		fileStream.read((char*)&record, sizeof(LogRecord));
		string mes(record.message);
		strRecord = "time: " + to_string(record.time) + "; message: " + mes + ";\n";
		logFile << strRecord;
	}
	logFile.close();
	fileStream.close();
}

Logger& Logger::operator<<(const LogRecord& record)
{
	fileStream.write((char*)&record, sizeof(record));
	return *this;
}

Logger& Logger::operator>>(LogRecord& record)
{
	fileStream.seekg(positionRead * sizeof(LogRecord), ios::beg);
	fileStream.read((char*)&record, sizeof(record));
	positionRead++;
	return *this;
}

bool Logger::operator!()
{
	return !fileStream;
}
