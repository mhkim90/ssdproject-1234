#include "command.h"
#include "../logger/Logger.h"

class ReadCommand : public CommandBase {
public:
	ReadCommand(ISSD& ssd)
		: CommandBase(ssd, 1)
	{
	}

	void execute(const vector<string>& args) override
	{
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Execute()");

		verifyArgsCount(args);
		verifyFormatAddress(args[0]);
		int addr = stoi(args[0]);
		verifyAddressRange(addr);
		std::cout << getSSD().read(addr) << "\n";
	}

	const string& getHelp() override {
		return _HELP_MESSAGE;
	}

private:
	const string _HELP_MESSAGE = "Reads the value written at LBA and displays it on the screen.\n\
		[Example] read [LBA]\n\
		[Parameters]\n\
		- LBA: LBA area value to read(0~99)\n\
		[Returns] Displays the data read from LBA.\n";
};

class FullReadCommand : public CommandBase {
public:
	FullReadCommand(ISSD& ssd)
		: CommandBase(ssd) {

	}

	void execute(const vector<string>& args) override
	{
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Execute()");

		for (int i = _ADDR_RANGE_MIN; i <= _ADDR_RANGE_MAX; i++) {
			std::cout << getSSD().read(i) << "\n";
		}
	}

	const string& getHelp() override
	{
		return _HELP_MESSAGE;
	}

private:
	const string _HELP_MESSAGE = "Reads and displays values from LBA 0 to 99 on the screen.\n\
		[Example] fullread\n\
		[Parameter] None\n\
		[Returns] Displays the data read from each LBA.\n";

};