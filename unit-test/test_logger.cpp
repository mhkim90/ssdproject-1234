#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../logger/Logger.cpp"
#include <filesystem>
#include <vector>
#include <fstream>

class LoggerFixture : public ::testing::Test {
public:
	std::string module_name = "gtest";
	ILogger& logger = Logger::getInstance(module_name);
	std::string name = "func()";
	std::string msg = "test message";
	const int m_name_buffer = 30;
	const int m_max_line = 2000;

	bool checkFiles(const std::vector<std::string>& file_names) const {
		size_t found = 0;
		size_t line = 0;
		for (const auto& file_name : file_names) {
			if (file_name.find("latest.log") != -1) {
				found++;
			}
			else if (file_name.find(".log") != -1) {
				found++;
			}
			else if (file_name.find(".zip") != -1) {
				found++;
			}
			line += getMaxLine(file_name);
		}

		if (file_names.size() == found && line == m_max_line) {
			return true;
		}
		return false;
	}

private:
	size_t getMaxLine(const std::string& file_name) const {
		std::ifstream aFile(file_name);
		std::size_t line_count = 0;
		std::string line;
		while (std::getline(aFile, line)) {
			++line_count;
		}
		return line_count;
	}
};

TEST_F(LoggerFixture, ConsoleTest) {
	testing::internal::CaptureStdout();
	logger.printLog(PRINT_TYPE::CONSOLE, name, msg);
	std::string captured_out = testing::internal::GetCapturedStdout();
	size_t begin_idx = captured_out.find_last_of(")");
	size_t end_idx = captured_out.find_last_of(":");
	EXPECT_EQ(end_idx - begin_idx - 1, m_name_buffer - name.size());
}

TEST_F(LoggerFixture, FileTest) {
	for (int i = 0; i < m_max_line; i++) {
		logger.printLog(PRINT_TYPE::FILE, name, msg);
	}
	
	std::vector<std::string> file_names;
	for (const auto& dir_entry : 
		std::filesystem::directory_iterator{ module_name }) {
		file_names.push_back(dir_entry.path().string());
	}
	EXPECT_TRUE(checkFiles(file_names));
}