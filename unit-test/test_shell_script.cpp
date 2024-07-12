#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../test-shell/ssd.h"
#include "../test-shell/ssdlib.h"
#include "../test-shell/command.h"
#include "../test-shell/command_factory.h"
#include "../test-shell/ReadCommand.h"
#include "../test-shell/WriteCommand.h"
#include "../test-shell/FlushCommand.h"
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
		, flushCommad(ssd)
		, factory { CommandFactory::getInstance() }
		, launcher { ssd, "TestScript1" }
	{
	}

	MockSSD ssd;
	ReadCommand readCommad;
	WriteCommand writeCommad;
	FlushCommand flushCommad;
	ICommandFactory& factory;
	ScriptLauncher launcher;

protected:
	void SetUp() override {
		factory.injectCommand("read", &readCommad);
		factory.injectCommand("write", &writeCommad);
		factory.injectCommand("flush", &flushCommad);
	}
};


TEST_F(ScriptLauncherFixture, TestScript1_NORMAL) {
	EXPECT_CALL(ssd, write(_, _))
		.Times(20);
	EXPECT_CALL(ssd, read(_))
		.Times(10)
		.WillRepeatedly(Return("0xAAAABBBB"));
	EXPECT_CALL(ssd, flush)
		.Times(2);
	
	EXPECT_NO_THROW(launcher.compile());
	EXPECT_EQ(launcher.getHelp(), "HELP MESSAGE");

	internal::CaptureStdout();

	EXPECT_NO_THROW(launcher.execute({}));
	EXPECT_NO_THROW(launcher.execute({}));

	EXPECT_EQ(internal::GetCapturedStdout(), "TestScript1 --- Run...Pass\nTestScript1 --- Run...Pass\n");
}

TEST_F(ScriptLauncherFixture, TestScript1_VERIFY_FAIL) {
	EXPECT_CALL(ssd, write(_, _))
		.Times(10);
	EXPECT_CALL(ssd, read(_))
		.Times(3)
		.WillRepeatedly(Return("0xAAAAAAAA"));
	EXPECT_CALL(ssd, flush())
		.Times(0);
	
	EXPECT_NO_THROW(launcher.compile());

	internal::CaptureStdout();

	EXPECT_THROW(launcher.execute({}), logic_error);

	EXPECT_EQ(internal::GetCapturedStdout(), "TestScript1 --- Run...FAIL!\n");
}