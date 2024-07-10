#pragma once
#include "ILogger.h"

class Logger : public ILogger {
public:
	static Logger& getInstance(const std::string& module_name);

	void printLog(PRINT_TYPE type,
		const std::string& func_name,
		const std::string& message) override;


private:
	Logger(const std::string& module_name);

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	std::string getTime();
	std::string expandName(const std::string& func_name);

	void saveLog(const std::string& output);

	std::string m_module_name;
	const int m_name_buffer = 30;
};