#pragma once
#include "ILogger.h"

class Logger : public ILogger {
public:
	static Logger& getInstance(const std::string& module_name);

	void writeLog(
		const std::string& func_name,
		const std::string& message) override;

private:
	Logger(const std::string& module_name);

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	std::string m_module_name;
};