#include "command.h"

class TestApp1Command : public ScriptBase {
public:
	TestApp1Command(ISSD& ssd)
		: ScriptBase(ssd, "testapp1") {
	}

	void execute(const vector<string>& args) override
	{
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Execute()");

		printRun();
		for (int addr = _ADDR_RANGE_MIN; addr <= _ADDR_RANGE_MAX; addr++) {
			getSSD().write(addr, TEST_VAL);
		}

		for (int i = _ADDR_RANGE_MIN; i <= _ADDR_RANGE_MAX; i++) {
			string tmp =getSSD().read(i);
			if (tmp != TEST_VAL) {
				printResult(false); // 여기서 throw 발생
			}
		}
		printResult(true);

		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Execute()");
	}

	const string& getHelp() override
	{
		return strHelp;
	}

private:
	const string TEST_VAL = "0xAAAABBBB";
	const string strHelp = "Test script1 - testapp1.\n\
		[Example] testapp1\n\
		[Parameters]\n\
		- None \n\
		[Returns] Display Pass or Fail\n";

};