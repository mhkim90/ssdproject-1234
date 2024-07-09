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

	ostringstream osstream;
	auto oldStreamBuf = cout.rdbuf();
	cout.set_rdbuf(osstream.rdbuf());

	shell.run();

	cout.set_rdbuf(oldStreamBuf);
	cout.clear();

	EXPECT_EQ(osstream.str(), "INVALID COMMAND\n");
}