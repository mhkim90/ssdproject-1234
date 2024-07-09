#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../test-shell/shell.cpp"
#include <unordered_map>
#include <string>


using namespace std;
using namespace testing;

class MockCommandFactory : public ICommandFactory {
public:
	MOCK_METHOD(void, injectCommand, (const string&, ICommand*), (override));
	MOCK_METHOD(ICommand*, getCommand, (const string&), (override));
	MOCK_METHOD((unordered_map<string,ICommand*>&), getAllCommands, (), (override));
};

class ShellFixutre : public Test {
public:
	ShellFixutre()
		: shell{ mockFactory }, _oldStreamBuf{ nullptr } {

	}

	void inputCommand(const string& inputStr) {
		_stringStream.str(inputStr);
		cin.set_rdbuf(_stringStream.rdbuf());
	}

	MockCommandFactory mockFactory;
	Shell shell;

protected:
	void SetUp() override {
		_oldStreamBuf = cin.rdbuf();
	}
	
	void TearDown() override {
		cin.set_rdbuf(_oldStreamBuf);
		cin.clear();
	}

private:
	istringstream _stringStream;
	streambuf* _oldStreamBuf;
};

TEST_F(ShellFixutre, WAIT_FOR_COMMAND_READ_EXIT) {
	inputCommand("exit");

	EXPECT_EQ(shell.waitForCommand(), "exit");
}


TEST_F(ShellFixutre, WAIT_FOR_COMMAND_READ_HELP) {
	inputCommand("help");

	EXPECT_EQ(shell.waitForCommand(), "help");
}