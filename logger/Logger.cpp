#include "Logger.h"
#include <filesystem>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>

Logger::Logger(const std::string& log_directory) {
	setDirectory(log_directory);
}

void Logger::setDirectory(const std::string& log_directory) {
	m_log_directory = log_directory;
	if (std::filesystem::exists(m_log_directory)) {
		std::filesystem::remove_all(m_log_directory);
	}
	std::filesystem::create_directory(m_log_directory);
}

Logger& Logger::getInstance(const std::string& log_directory) {
	static Logger instance(log_directory);
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

int Logger::getFileSize(const std::string& file_path) {
	if (std::filesystem::exists(file_path)) {
		return static_cast<int>(std::filesystem::file_size(file_path));
	}
	return 0;
}

void Logger::saveLog(const std::string& output) {
	if (getFileSize(m_log_directory + m_file_name) > m_ten_kb) {
		std::string previous_file_path =
			m_log_directory + m_past_log_file_name;

		if (m_past_log_file_name != "" &&
			std::filesystem::exists(previous_file_path + ".log")) {
			std::filesystem::rename(
				previous_file_path + ".log",
				previous_file_path + ".zip");
		}

		m_past_log_file_name = getPastLogFileName();
		std::filesystem::rename(m_log_directory + m_file_name,
			m_log_directory + m_past_log_file_name + ".log");
	}

	std::ofstream file;
	file.open(m_log_directory + m_file_name,
		std::ios::out | std::ios::app);
	file << output << "\n";
	file.close();
}

std::string Logger::expandName(const std::string& func_name) const {
	size_t name_size_limit = 27;
	if (func_name.size() < name_size_limit) {
		std::string expanded_func_name = func_name;
		for (size_t i = 0; i < m_name_buffer - func_name.size(); i++) {
			expanded_func_name.append(" ");
		}
		return expanded_func_name;
	}
	else {
		std::string reduced_func_name = 
			func_name.substr(0, name_size_limit - 2);
		reduced_func_name.append("...()");
		return reduced_func_name;
	}
}

std::string Logger::getPastLogFileName() {
	std::string file_name =
		"\\until_" + getTime("%Y%m%d_%Hh_%Mm_%Ss", true);
	return file_name;
}

std::string Logger::getTime(const std::string& format,
		bool add_ms) {
	auto time_now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>
		(time_now.time_since_epoch()) % 1000;
    time_t current_time_t = std::chrono::system_clock::to_time_t(
		time_now);
    tm current_time;
    localtime_s(&current_time, &current_time_t);
	std::stringstream converted_time;
	converted_time << std::put_time(
		&current_time, format.c_str());
	if (add_ms) {
		converted_time << '_' << std::setfill('0') << std::setw(3) << ms.count() << "ms";
		return converted_time.str();
	}
	return converted_time.str();
}

std::string Logger::getTime() {
	return getTime("[%Y.%m.%d %H:%M] ", false);
}