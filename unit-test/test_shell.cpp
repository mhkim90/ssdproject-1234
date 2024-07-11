#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../test-shell/shell.h"
#include "../test-shell/ssd.h"
#include "../test-shell/ReadCommand.h"
#include "../test-shell/WriteCommand.h"
#include "../test-shell/TestApp1Command.h"
#include "../test-shell/TestApp2Command.h"
#include "../test-shell/FlushCommand.h"
#include "../test-shell/EraseCommand.h"
#include "../test-shell/EraseRangeCommand.h"
#include "../test-shell/command_factory.h"
#include <unordered_map>
#include <string>


using namespace std;
using namespace testing;

class MockSSD : public ISSD {
public:
	MOCK_METHOD(void, write, (int, const string&), (override));
	MOCK_METHOD(string, read, (int), (override));
	MOCK_METHOD(void, erase, (int, int), (override));
	MOCK_METHOD(void, flush, (), (override));
};

class MockCommand : public ICommand {
public:
	MOCK_METHOD(void, injectSSD, (ISSD&), (override));
	MOCK_METHOD(void, execute, (const vector<string>&), (override));
	MOCK_METHOD(const string&, getHelp, (), (override));
	string _helpMessage = "HELP MESSAGE";
};

class MockCommandFactory : public ICommandFactory {
public:
	MOCK_METHOD(void, injectCommand, (const string&, ICommand*), (override));
	MOCK_METHOD(ICommand*, getCommand, (const string&), (override));
	MOCK_METHOD((const unordered_map<string, ICommand*>&), getAllCommands, (), (const override));
	MOCK_METHOD(void, initialize, (ISSD*), (override));
	unordered_map<string, ICommand*> _commands;
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

	string makeOutputFormat(const string& value) {
		if (value.empty()) return SHELL_GUIDE;
		return SHELL_GUIDE + value + SHELL_GUIDE;
	}

	MockCommand mockCommand;
	MockCommandFactory mockFactory;
	Shell shell;

protected:
	void SetUp() override {
		_inOldStreamBuf = cin.rdbuf();
		_outOldStreamBuf = cout.rdbuf();
		cout.set_rdbuf(_osstream.rdbuf());

		mockFactory._commands["command"] = &mockCommand;
	}
	
	void TearDown() override {
		cin.set_rdbuf(_inOldStreamBuf);
		cin.clear();

		cout.set_rdbuf(_outOldStreamBuf);
		cout.clear();
	}

private:
	static constexpr char* SHELL_GUIDE = "SHELL > ";

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

TEST_F(ShellFixutre, COMMAND_RUN_INVALID_COMMAND_EMPTY) {
	inputCommand("\nexit");

	shell.run();

	EXPECT_EQ(getOutput(), makeOutputFormat("") + makeOutputFormat(""));
}

TEST_F(ShellFixutre, COMMAND_RUN_INVALID_COMMAND_UNKNOWN) {
	inputCommand("unknown\nexit");

	EXPECT_CALL(mockFactory, getCommand(_))
		.Times(1)
		.WillRepeatedly(Throw(invalid_argument("INVALID COMMAND")));

	shell.run();

	EXPECT_EQ(getOutput(), makeOutputFormat("INVALID COMMAND\n"));
}

TEST_F(ShellFixutre, COMMAND_RUN_EXIT) {
	inputCommand("exit");

	shell.run();

	EXPECT_EQ(getOutput(), makeOutputFormat(""));
}

TEST_F(ShellFixutre, COMMAND_RUN_HELP) {
	inputCommand("help\nexit");

	EXPECT_CALL(mockCommand, getHelp)
		.Times(1)
		.WillRepeatedly(ReturnRef(mockCommand._helpMessage));

	EXPECT_CALL(mockFactory, getAllCommands)
		.Times(1)
		.WillRepeatedly(ReturnRef(mockFactory._commands));

	shell.run();

	EXPECT_EQ(getOutput(), makeOutputFormat("< Help >\ncommand\t\t: HELP MESSAGE\n"));
}

TEST_F(ShellFixutre, RUN_SEQUENCE_INVALID_FILE_PATH) {
	EXPECT_THROW(shell.loadSequence("unknown.list"), invalid_argument);
	EXPECT_THROW(shell.loadSequence(""), invalid_argument);
	EXPECT_THROW(shell.loadSequence("."), invalid_argument);
}

TEST_F(ShellFixutre, LOAD_SEQ) {
	EXPECT_NO_THROW(shell.loadSequence("test_run_list.lst"));
	EXPECT_EQ(shell.getSequence().size(), 2);
	EXPECT_THAT(shell.getSequence(), Contains("testapp1"));
	EXPECT_THAT(shell.getSequence(), Contains("testapp2"));
}

class ShellRunSeqFixutre : public Test {
public:
	ShellRunSeqFixutre()
		: factory{ CommandFactory::getInstance() }
		, shell{ CommandFactory::getInstance() }
		, cmdTestApp1(mockSSD)
		, cmdTestApp2(mockSSD)
	{
		factory.injectCommand("testapp1", &cmdTestApp1);
		factory.injectCommand("testapp2", &cmdTestApp2);
	}

	Shell shell;
	ICommandFactory& factory;
	TestApp1Command cmdTestApp1;
	TestApp2Command cmdTestApp2;
	MockSSD mockSSD;
};

TEST_F(ShellRunSeqFixutre, RUN_SEQ) {
	int readCallCount = 0;

	EXPECT_CALL(mockSSD, write(_, _))
		.Times(286);

	EXPECT_CALL(mockSSD, read(_))
		.WillRepeatedly(InvokeWithoutArgs([&readCallCount]() {
		if (readCallCount < 100) {
			++readCallCount;
			return string{ "0xAAAABBBB" };
		}
		return string{ "0x12345678" };
			}));

	internal::CaptureStdout();
	EXPECT_NO_THROW(shell.runSequence("test_run_list.lst"));

	EXPECT_EQ(internal::GetCapturedStdout(), "testapp1 --- Run...Pass\ntestapp2 --- Run...Pass\n");
}

TEST_F(ShellRunSeqFixutre, LOAD_SCRIPTS) {
	EXPECT_EQ(shell.loadScripts(mockSSD), 1);
	EXPECT_NO_THROW(factory.getCommand("TestScript1"));
	EXPECT_THAT(factory.getCommand("TestScript1"), NotNull());
}