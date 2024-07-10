#pragma once
#include <string>

enum class PRINT_TYPE {
	FILE,
	CONSOLE,
	ALL
};

class ILogger {
public:
	virtual void printLog(PRINT_TYPE type,
		const std::string& func_name,
		const std::string& message) = 0;
};