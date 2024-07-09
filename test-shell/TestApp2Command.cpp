#include <string>
#include <stdexcept>
#include <regex>
#include "command.h"
#include "Printer.cpp"

class TestApp2Command : public ICommand {
public:
	TestApp2Command(ISSD& ssd) : ssd{ ssd } {}

	void injectSSD(ISSD& ssd) override
	{
		this->ssd = ssd;
	}

	void execute(const vector<string>& args) override
	{
		std::string  agingString = "0xAAAABBBB";
		std::string  originString = "0x12345678";
		Printer& printer = Printer::getInstance();

		// no argument to check
		// 
		// act
		// 1st step
		for (int lba = START_LBA_FOR_AGING; lba <= END_LBA_FOR_AGING; lba++) {
			for (int tryCount = 0; tryCount < WRITE_TRY_MAX; tryCount++) {
				ssd.write(lba, agingString);
			}
		}

		// 2nd step
		for (int lba = START_LBA_FOR_AGING; lba <= END_LBA_FOR_AGING; lba++) {
			ssd.write(lba, originString);
		}

		// 3rd step
		for (int lba = START_LBA_FOR_AGING; lba <= END_LBA_FOR_AGING; lba++) {
			if (originString != ssd.read(lba)) {
				printer.print("FAIL");
				return;
			}
		}

		printer.print("SUCCESS");
	}

	const string& getHelp() override
	{
		return WRITE_HELP;
	}

private:
	ISSD& ssd;

	const string WRITE_HELP = "Test script2 - testapp2. \n\
		[Example] testapp2\n\
		[Parameters]\n\
		- none \n\
		[Returns] result SUCCESS/FAIL\n";
	const int WRITE_TRY_MAX = 30;
	const int START_LBA_FOR_AGING = 0;
	const int END_LBA_FOR_AGING = 5;

};
