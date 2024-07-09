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
	MOCK_METHOD((unordered_map<string, ICommand*>&), getAllCommands, (), (const override));
};

class ShellFixutre : public Test {
public:
	ShellFixutre()
		: shell{ mockFactory }
		, _inOldStreamBuf{ nullptr }
		, _outOldStreamBuf{ nullptr } {

	}

	void inputCommand(const string& inputStr) {
		_isstream.str(inputStr);
		cin.set_rdbuf(_isstream.rdbuf());
	}

	string getOutput() {
		return _osstream.str();
	}

	MockCommandFactory mockFactory;
	Shell shell;

protected:
	void SetUp() override {
		_inOldStreamBuf = cin.rdbuf();
		_outOldStreamBuf = cout.rdbuf();
		cout.set_rdbuf(_osstream.rdbuf());
	}
	
	void TearDown() override {
		cin.set_rdbuf(_inOldStreamBuf);
		cin.clear();

		cout.set_rdbuf(_outOldStreamBuf);
		cout.clear();
	}

private:
	istringstream _isstream;
	ostringstream _osstream;
	streambuf* _inOldStreamBuf;
	streambuf* _outOldStreamBuf;
};

TEST_F(ShellFixutre, WAIT_FOR_COMMAND_READ_EXIT) {
	inputCommand("exit");

	EXPECT_EQ(shell.waitForCommand(), "exit");
}

TEST_F(ShellFixutre, WAIT_FOR_COMMAND_READ_HELP) {
	inputCommand("help");

	EXPECT_EQ(shell.waitForCommand(), "help");
}

TEST_F(ShellFixutre, WAIT_FOR_COMMAND_READ_WIRTE) {
	inputCommand("write 0 0xAAAABBBB");

	EXPECT_EQ(shell.waitForCommand(), "write 0 0xAAAABBBB");
}

TEST_F(ShellFixutre, WAIT_FOR_COMMAND_READ_READ) {
	inputCommand("read 0");

	EXPECT_EQ(shell.waitForCommand(), "read 0");
}

TEST_F(ShellFixutre, COMMAND_STR_PARSING_INVALID_ARGUMENT) {
	inputCommand("");

	string commandStr = shell.waitForCommand();
	EXPECT_THROW(shell.parsingCommandStr(commandStr), invalid_argument);
}

TEST_F(ShellFixutre, COMMAND_STR_PARSING) {
	inputCommand("write 0  0xAAAABBBB");

	string commandStr = shell.waitForCommand();

	vector<string> expect;
	expect.push_back("write");
	expect.push_back("0");
	expect.push_back("0xAAAABBBB");
	EXPECT_EQ(shell.parsingCommandStr(commandStr), expect);
}

TEST_F(ShellFixutre, COMMAND_RUN_INVALID_COMMAND) {
	inputCommand("");

	shell.run();

	EXPECT_EQ(getOutput(), "INVALID COMMAND\n");
}

TEST_F(ShellFixutre, COMMAND_RUN_EXIT) {
	inputCommand("exit");

	shell.run();

	EXPECT_EQ(getOutput(), "");
}