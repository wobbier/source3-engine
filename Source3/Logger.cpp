// UWOTM8 Engine - 2014 Mitchell Andrews
#include "Logger.h"

Logger::Logger() {
}

Logger::~Logger() {
}

void Logger::SetLogFile(std::string filename) {
	mLogFileLocation = filename;
}

void Logger::SetLogPriority(LogType priority) {
	mPriority = priority;
}

bool Logger::Log(LogType priority, std::string message) {
	if (mPriority == NONE) return false;
	if (priority < mPriority)
		return false;

	mLogFile.open(mLogFileLocation, std::ios_base::app);

	char* type;
	switch (priority) {
	case INFO:
		type = "[Info]: ";
		break;
	case TRACE:
		type = "[Trace]: ";
		break;
	case DEBUG:
		type = "[Debug]: ";
		break;
	case WARN:
		type = "[Warning]: ";
		break;
	case ERR:
		type = "[Error]: ";
		break;
	default:
		type = "[Unknown]: ";
		break;
	}
	mLogFile << type << message.c_str() << std::endl;
	mLogFile.close();
	return true;
}