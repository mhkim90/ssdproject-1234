#include "Logger.h"
#include <filesystem>
#include <string>
#include <iostream>

Logger::Logger(const std::string& module_name) {
	m_module_name = module_name;
}

Logger& Logger::getInstance(const std::string& module_name) {
	static Logger instance(module_name);
	return instance;
}

void Logger::writeLog(
	const std::string& func_name,
	const std::string& message) {

}