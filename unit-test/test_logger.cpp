#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../logger/Logger.h"

TEST(LoggerTest, CoutTest) {
	std::string module_name = "gtest";
	ILogger& logger = Logger::getInstance(module_name);
	std::string name = "func()";
	std::string msg = "test message";
	const int m_name_buffer = 30;
	testing::internal::CaptureStdout();

	logger.printLog(PRINT_TYPE::CONSOLE, name, msg);
	std::string captured_out = testing::internal::GetCapturedStdout();
	int begin_idx = captured_out.find_last_of(")");
	int end_idx = captured_out.find_last_of(":");
	EXPECT_EQ(end_idx - begin_idx - 1, m_name_buffer - name.size());
}