#include "./headers/logger.h"

namespace Logger {
	void logInfo(const char* subject, const char* message) {
		std::cout << "[INFO] [" << subject << "] " << message << std::endl;
	}
	void logInfo(const char* subject, const std::string message) {
		logInfo(subject, message.c_str());
	}

	void logError(const char* subject, const char* message) {
		std::cerr << "[ERR ] [" << subject << "] " << message << std::endl;
	}
	void logError(const char* subject, const std::string message) {
		logError(subject, message.c_str());
	}

	void logWarning(const char* subject, const char* message) {
		std::cout << "[WARN] [" << subject << "] " << message << std::endl;
	}
	void logWarning(const char* subject, const std::string message) {
		logWarning(subject, message.c_str());
	}
}