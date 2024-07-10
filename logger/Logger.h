#pragma once
#include "ILogger.h"

class Logger : public ILogger {
public:
	static Logger& getInstance(const std::string& log_directory);

	void printLog(PRINT_TYPE type,
		const std::string& func_name,
		const std::string& message) override;


private:
	Logger(const std::string& log_directory);

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	std::string getTime();
	std::string getTime(const std::string& format, bool add_ms);
	std::string getPastLogFileName();
	std::string expandName(const std::string& func_name) const;
	int getFileSize(const std::string& file_path);

	void saveLog(const std::string& output);

	std::string m_log_directory;
	std::string m_past_log_file_name = "";
	const int m_name_buffer = 30;
	const int m_ten_kb = 10 * 1024;
	const std::string m_file_name = "\\latest.log";
};