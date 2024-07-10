#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../test-shell/command_factory.cpp"
#include "../test-shell/command.h"
#include "../test-shell/ssdlib.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
using namespace std;
using namespace testing;

class MockWriteCMD : public ICommand {
public:
	MOCK_METHOD(void, execute, (const vector<string>&), (override));
	MOCK_METHOD(string&, getHelp, (), (override));
	MOCK_METHOD(void, injectSSD, (ISSD&), (override));
};

class MockReadCMD : public ICommand {
public:
	MOCK_METHOD(void, execute, (const vector<string>&), (override));
	MOCK_METHOD(string&, getHelp, (), (override));
	MOCK_METHOD(void, injectSSD, (ISSD&), (override));
};

class FactoryFixture : public ::testing::Test {
public:
	MockReadCMD readCMD;
	MockWriteCMD writeCMD;
	MockWriteCMD testCMD;

	vector<string> dummy_args;

	ICommandFactory& factory = CommandFactory::getInstance();
private:

protected:
	void SetUp() override {
		dummy_args = { "0", "0" };

		factory.injectCommand("read", &readCMD);
		factory.injectCommand("write", &writeCMD);
	}

	void TearDown() override {

	}
};

TEST_F(FactoryFixture, TestInjectedReadCommand) {
	EXPECT_CALL(readCMD, execute(_))
		.Times(1);
	EXPECT_CALL(writeCMD, execute(_))
		.Times(0);
	ICommand* command = factory.getCommand("read");
	command->execute(dummy_args);
}

TEST_F(FactoryFixture, TestInjectedWriteCommand) {
	EXPECT_CALL(readCMD, execute(_))
		.Times(0);
	EXPECT_CALL(writeCMD, execute(_))
		.Times(1);
	ICommand* command = factory.getCommand("write");
	command->execute(dummy_args);
}

TEST_F(FactoryFixture, TestThrowgetCommand) {
	EXPECT_THROW(factory.getCommand("test"), std::invalid_argument);
}

TEST_F(FactoryFixture, TestgetAllCommands) {
	EXPECT_CALL(readCMD, execute(_))
		.Times(1);
	EXPECT_CALL(writeCMD, execute(_))
		.Times(1);
	const unordered_map<string, ICommand*>& commands = factory.getAllCommands();
	EXPECT_EQ(commands.size(), 2);
	for (auto& command : commands) {
		command.second->execute(dummy_args);
	}
}