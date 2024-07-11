#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../test-shell/ssd.h"
#include "../test-shell/ssdlib.h"
#include "../test-shell/command.h"
#include "../test-shell/command_factory.h"
#include "../test-shell/ReadCommand.h"
#include "../test-shell/WriteCommand.h"
#include "../test-shell/ScriptLauncher.h"

using namespace std;
using namespace testing;

class MockSSD : public ISSD {
public:
	MOCK_METHOD(void, write, (int, const string&), (override));
	MOCK_METHOD(string, read, (int), (override));
	MOCK_METHOD(void, erase, (int, int), (override));
	MOCK_METHOD(void, flush, (), (override));
};


TEST(Script_Launcher_Test, TestScript1) {
	MockSSD ssd;
	EXPECT_CALL(ssd, write(_, _))
		.Times(1);

	EXPECT_CALL(ssd, read(_))
		.Times(1)
		.WillRepeatedly(Return("0xAAAABBBB"));

	ReadCommand readCommad(ssd);
	WriteCommand writeCommad(ssd);
	ICommandFactory& factory = CommandFactory::getInstance();
	factory.injectCommand("read", &readCommad);
	factory.injectCommand("write", &writeCommad);
	
	ScriptLauncher launcher(ssd, "TestScript1");
	
	EXPECT_NO_THROW(launcher.load());
	EXPECT_EQ(launcher.getHelp(), "HELP MESSAGE");

	internal::CaptureStdout();

	EXPECT_NO_THROW(launcher.execute({}));

	EXPECT_EQ(internal::GetCapturedStdout(), "TestScript1 --- Run...Pass\n");
}