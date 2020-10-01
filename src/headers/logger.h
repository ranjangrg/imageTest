#ifndef __LOGGER_H
#define __LOGGER_H

#include <iostream>
#include <string>

namespace Logger {
	void logInfo(const char* subject, const char* message);
	void logInfo(const char* subject, const std::string message);

	void logError(const char* subject, const char* message);
	void logError(const char* subject, const std::string message);

	void logWarning(const char* subject, const char* message);
	void logWarning(const char* subject, const std::string message);
}

#endif