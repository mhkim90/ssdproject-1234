#include "ReadCommand.h"

ReadCommand::ReadCommand(ISSD& ssd)
	: CommandBase(ssd, 1)
	, _HELP_MESSAGE{string{"Reads the value written at LBA and displays it on the screen.\n\
		[Example] read [LBA]\n\
		[Parameters]\n\
		- LBA: LBA area value to read(0~99)\n\
		[Returns] Displays the data read from LBA.\n"}}
{
}

void ReadCommand::execute(const vector<string>& args)
{
	verifyArgsCount(args);

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Read " + args[0] + " Execute()");

	verifyFormatAddress(args[0]);
	int addr = stoi(args[0]);
	verifyAddressRange(addr);
	std::cout << getSSD().read(addr) << "\n";

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Execute()");
}

const string& ReadCommand::getHelp()
{
	return _HELP_MESSAGE;
}

FullReadCommand::FullReadCommand(ISSD& ssd)
	: CommandBase(ssd)
	, _HELP_MESSAGE{ string{"Reads and displays values from LBA 0 to 99 on the screen.\n\
		[Example] fullread\n\
		[Parameter] None\n\
		[Returns] Displays the data read from each LBA.\n"} }
{
}

void FullReadCommand::execute(const vector<string>& args)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start FullRead Execute()");

	for (int i = _ADDR_RANGE_MIN; i <= _ADDR_RANGE_MAX; i++) {
		std::cout << getSSD().read(i) << "\n";
	}
}

const string& FullReadCommand::getHelp()
{
	return _HELP_MESSAGE;
}
