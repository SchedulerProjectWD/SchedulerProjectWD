#include "Logger.h"
#include "LogRecord.h"

Logger::Logger(const char* path):positionRead(0) {

	fileStream.open(path, ios::in | ios::out | ios::app | ios::binary);
	if (!fileStream)
		throw exception("could not open file");
}

Logger::~Logger()
{
	fileStream.close();
}

Logger& Logger::operator<<(const LogRecord& record)
{
	//fileStream.open(path, ios::in | ios::out | ios::app | ios::binary);
	/*if (!fileStream)
		throw exception("could not open file");*/
	fileStream.write((char*)&record, sizeof(record));
	//fileStream.close();
	return *this;
}

Logger& Logger::operator>>(LogRecord& record)
{
	fileStream.seekg(positionRead*sizeof(LogRecord), ios::beg);
	fileStream.read((char*)&record, sizeof(record));
	positionRead++;
	return *this;
}

	//fileStream.open(path, ios::in | ios::out | ios::app | ios::binary);
	/*if (!fileStream)
		throw exception("could not open file");*/

	//fileStream.close();
bool Logger::operator!()
{
	return !fileStream;
}
