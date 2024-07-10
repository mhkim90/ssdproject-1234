#include <string>
#include <stdexcept>
#include <regex>
#include "command.h"

class TestApp2Command : public ScriptBase {
public:
	TestApp2Command(ISSD& ssd)
		: ScriptBase(ssd, "testapp2") {

	}

	void execute(const vector<string>& args) override
	{
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Execute()");

		std::string  agingString = "0xAAAABBBB";
		std::string  originString = "0x12345678";

		printRun();

		// no argument to check
		// 
		// act
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
				printResult(false); // 여기서 throw 발생
			}
		}

		printResult(true);
	}

	const string& getHelp() override
	{
		return WRITE_HELP;
	}

private:
	const string WRITE_HELP = "Test script2 - testapp2. \n\
		[Example] testapp2\n\
		[Parameters]\n\
		- none \n\
		[Returns] result SUCCESS/FAIL\n";
	const int WRITE_TRY_MAX = 30;
	const int START_LBA_FOR_AGING = 0;
	const int END_LBA_FOR_AGING = 5;

};
