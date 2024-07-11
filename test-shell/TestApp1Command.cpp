#include "TestApp1Command.h"

TestApp1Command::TestApp1Command(ISSD & ssd)
	: ScriptBase(ssd, "testapp1")
	, TEST_VAL{ "0xAAAABBBB" }
	, strHelp{ string{"Test script1 - testapp1.\n\
		[Example] testapp1\n\
		[Parameters]\n\
		- None \n\
		[Returns] Display Pass or Fail\n"} }
{
}

void TestApp1Command::execute(const vector<string>& args)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Execute()");

	printRun();
	for (int addr = _ADDR_RANGE_MIN; addr <= _ADDR_RANGE_MAX; addr++) {
		getSSD().write(addr, TEST_VAL);
	}

	for (int i = _ADDR_RANGE_MIN; i <= _ADDR_RANGE_MAX; i++) {
		string tmp = getSSD().read(i);
		if (tmp != TEST_VAL) {
			printResult(false);
		}
	}
	printResult(true);

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Execute()");
}

const string& TestApp1Command::getHelp()
{
	return strHelp;
}