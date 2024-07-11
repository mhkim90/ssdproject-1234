#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../test-shell/ssd.h"
#include "../test-shell/ssdlib.h"
#include "../test-shell/command.h"
#include "../test-shell/command_factory.h"
#include "../test-shell/ReadCommand.h"
#include "../test-shell/WriteCommand.h"
#include "../test-shell/ScriptLauncher.h"
#include "../test-shell/shell.h"

using namespace std;
using namespace testing;

class MockSSD : public ISSD {
public:
	MOCK_METHOD(void, write, (int, const string&), (override));
	MOCK_METHOD(string, read, (int), (override));
	MOCK_METHOD(void, erase, (int, int), (override));
	MOCK_METHOD(void, flush, (), (override));
};

class ScriptLauncherFixture : public Test {
public:
	ScriptLauncherFixture()
		: ssd{}
		, readCommad(ssd)
		, writeCommad(ssd)
		, factory { CommandFactory::getInstance() }
		, shell { factory }
	{
	}

	MockSSD ssd;
	ReadCommand readCommad;
	WriteCommand writeCommad;
	ICommandFactory& factory;
	Shell shell;

protected:
	void SetUp() override {
		factory.injectCommand("read", &readCommad);
		factory.injectCommand("write", &writeCommad);
	}
};


TEST_F(ScriptLauncherFixture, TestScript1_NORMAL) {

	ScriptLauncher launcher(ssd, "TestScript1");

	EXPECT_CALL(ssd, write(_, _))
		.Times(1);

	EXPECT_CALL(ssd, read(_))
		.Times(1)
		.WillRepeatedly(Return("0xAAAABBBB"));
	
	EXPECT_NO_THROW(launcher.compile());
	EXPECT_EQ(launcher.getHelp(), "HELP MESSAGE");

	internal::CaptureStdout();

	EXPECT_NO_THROW(launcher.execute({}));

	EXPECT_EQ(internal::GetCapturedStdout(), "TestScript1 --- Run...Pass\n");
}

TEST_F(ScriptLauncherFixture, TestScript1_VERIFY_FAIL) {

	ScriptLauncher launcher(ssd, "TestScript1");

	EXPECT_CALL(ssd, write(_, _))
		.Times(1);

	EXPECT_CALL(ssd, read(_))
		.Times(1)
		.WillRepeatedly(Return("0xAAAAAAAA"));
	
	EXPECT_NO_THROW(launcher.compile());
	EXPECT_EQ(launcher.getHelp(), "HELP MESSAGE");

	internal::CaptureStdout();

	EXPECT_THROW(launcher.execute({}), logic_error);

	EXPECT_EQ(internal::GetCapturedStdout(), "TestScript1 --- Run...FAIL!\n");
}

TEST_F(ScriptLauncherFixture, Shell_LoadScript) {
	EXPECT_EQ(shell.loadScripts(ssd), 1);
	EXPECT_NO_THROW(factory.getCommand("TestScript1"));
	EXPECT_THAT(factory.getCommand("TestScript1"), NotNull());
}