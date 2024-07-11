#include "TestApp2Command.h"

TestApp2Command::TestApp2Command(ISSD& ssd)
	: ScriptBase(ssd, "testapp2")
	, WRITE_HELP{ string{"Test script2 - testapp2. \n\
		[Example] testapp2\n\
		[Parameters]\n\
		- none \n\
		[Returns] result SUCCESS/FAIL\n"} }
	, WRITE_TRY_MAX {30}
	, START_LBA_FOR_AGING {0}
	, END_LBA_FOR_AGING {5}
{
}

void TestApp2Command::execute(const vector<string>& args)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start TestApp2 Execute()");

	std::string  agingString = "0xAAAABBBB";
	std::string  originString = "0x12345678";

	printRun();

	// 1st step
	for (int lba = START_LBA_FOR_AGING; lba <= END_LBA_FOR_AGING; lba++) {
		for (int tryCount = 0; tryCount < WRITE_TRY_MAX; tryCount++) {
			getSSD().write(lba, agingString);
		}
	}

	// 2nd step
	for (int lba = START_LBA_FOR_AGING; lba <= END_LBA_FOR_AGING; lba++) {
		getSSD().write(lba, originString);
	}

	// 3rd step
	for (int lba = START_LBA_FOR_AGING; lba <= END_LBA_FOR_AGING; lba++) {
		if (originString != getSSD().read(lba)) {
			printResult(false);
		}
	}

	printResult(true);

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Execute()");
}

const string& TestApp2Command::getHelp()
{
	return WRITE_HELP;
}
