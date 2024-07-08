#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../test-shell/shell.cpp"


using namespace testing;

class MockCommandFactory : public ICommandFactory {
public:
};

TEST(SHELL_TEST, WAIT_FOR_COMMAND_READ) {
	MockCommandFactory mockFactory;
	Shell shell(mockFactory);

	std::istringstream stringStream("exit");
	auto oldStreamBuf = cin.rdbuf();
	cin.set_rdbuf(stringStream.rdbuf());
	
	string rst = shell.waitForCommand();

	EXPECT_EQ(rst, "exit");

	cin.set_rdbuf(oldStreamBuf);
}