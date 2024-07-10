#pragma once
#include <string>

class ILogger {
public:
	virtual void writeLog(
		const std::string& func_name,
		const std::string& message) = 0;
};