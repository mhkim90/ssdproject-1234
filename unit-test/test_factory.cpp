#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../test-shell/command_factory.cpp"
#include "../test-shell/command.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
using namespace testing;

class MockWriteCMD : public ICommand {
public:
	MOCK_METHOD(void, execute, (CommandArgs&), (override));
	MOCK_METHOD(string&, getHelp, (), (override));
	MOCK_METHOD(void, injectSSD, (ISSD&), (override));
};

class MockReadCMD : public ICommand {
public:
	MOCK_METHOD(void, execute, (CommandArgs&), (override));
	MOCK_METHOD(string&, getHelp, (), (override));
	MOCK_METHOD(void, injectSSD, (ISSD&), (override));
};

class FactoryFixture : public ::testing::Test {
public:
	MockReadCMD readCMD;
	MockWriteCMD writeCMD;

	CommandArgs dummy_args{ 0, "0" };

	ICommandFactory& factory = CommandFactory::getInstance();
private:

protected:
	void SetUp() override {
		factory.injectCommand("read", &readCMD);;
		factory.injectCommand("write", &writeCMD);;
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