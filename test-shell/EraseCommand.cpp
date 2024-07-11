#include "EraseCommand.h"

EraseCommand::EraseCommand(ISSD& ssd)
	: CommandBase(ssd, 2)
	, _HELP_MESSAGE{ string{"Erase contents from a specific LBA to a specific size.\n\
		[Example] erase [LBA] [Size]\n\
		[Parameters]\n\
		- LBA: LBA area value to read(0~99)\n\
		- Size: Size of LBA of deleted(0~100)\n\
		[Returns] None\n"} }
	, MIN_ERASE_SIZE { 0 }
	, MAX_ERASE_SIZE { 10 }
{
}

void EraseCommand::execute(const vector<string>& args)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Execute()");

	verifyArgsCount(args);
	verifyFormatAddress(args[0]);
	verifyFormatAddress(args[1]);
	int addr = stoi(args[0]);
	int size = stoi(args[1]);
	verifyAddressRange(addr);

	int tmpSize = size;
	int tmpAddr = addr;
	while (tmpSize > MIN_ERASE_SIZE && tmpAddr <= _ADDR_RANGE_MAX) {
		if (tmpSize >= MAX_ERASE_SIZE) {
			getSSD().erase(tmpAddr, MAX_ERASE_SIZE);
			tmpSize -= MAX_ERASE_SIZE;
			tmpAddr += MAX_ERASE_SIZE;
		}
		else {
			getSSD().erase(tmpAddr, tmpSize);
			tmpSize = 0;
		}

		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Execute()");
	}
}

const string& EraseCommand::getHelp()
{
	return _HELP_MESSAGE;
}
