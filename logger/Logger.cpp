#include "Logger.h"
#include <filesystem>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>

Logger::Logger(const std::string& module_name) {
	m_module_name = module_name;
	if (std::filesystem::exists(m_module_name)) {
		std::filesystem::remove_all(m_module_name);
	}
	std::filesystem::create_directory(m_module_name);
}

Logger& Logger::getInstance(const std::string& module_name) {
	static Logger instance(module_name);
	return instance;
}

void Logger::printLog(PRINT_TYPE type,
	const std::string& func_name,
	const std::string& message) {
	std::string output = getTime() + expandName(func_name) + ":"
		+ message;
	switch (type) {
		case PRINT_TYPE::FILE:
			saveLog(output);
			break;
		case PRINT_TYPE::CONSOLE:
			std::cout << output << std::endl;
			break;
		case PRINT_TYPE::ALL:
			std::cout << output << std::endl;
			saveLog(output);
			break;
		default:
			break;
	}
}

void Logger::saveLog(
	const std::string& output) {
	std::ofstream file;
	file.open(m_module_name + "\\latest.log",
		std::ios::out | std::ios::app);
	file << output << "\n";
	file.close();
}

std::string Logger::expandName(const std::string& func_name) {
	if (func_name.size() < m_name_buffer) {
		std::string expanded_func_name = func_name;
		for (size_t i = 0; i < m_name_buffer - func_name.size(); i++) {
			expanded_func_name.append(" ");
		}
		return expanded_func_name;
	}
	return func_name;
}

std::string Logger::getTime() {
    time_t current_time_t = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
    tm current_time;
    localtime_s(&current_time, &current_time_t);
	std::stringstream converted_time;
	converted_time << std::put_time(
		&current_time, "[%Y.%m.%d %H:%M] ");
	return converted_time.str();
}