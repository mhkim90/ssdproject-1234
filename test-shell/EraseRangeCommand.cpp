#include "EraseRangeCommand.h"
EraseRangeCommand::EraseRangeCommand(ISSD& ssd, int argsCount)
	: CommandBase(ssd, argsCount)
	, _HELP_MESSAGE{ string{"Delete a specific range of SSD.\n\
		[Example] erase START_LBA END_LBA\n\
		[Parameters]\n\
		- START_LBA: Start-address to delete(0~99)\n\
		- END_LBA: End-address to delete(1~100)\n\
		[Returns] None\n"} }
	, ERASE_SIZE_AT_ONCE { 10 }
	, ERASE_END_LBA { 100 }
{
}

void EraseRangeCommand::execute(const vector<string>& args)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__,
		"Start EraseRange " + args[0] + " " + args[1] + " Execute()");

	verifyArgsCount(args);
	verifyFormatAddress(args[0]);
	verifyFormatAddress(args[1]);

	int start_addr = stoi(args[0]);
	int end_addr = stoi(args[1]);

	verifyAddressRange(start_addr);
	if (end_addr > ERASE_END_LBA) {
		end_addr = ERASE_END_LBA;
	}

	if (start_addr >= end_addr) {
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Exception: Invalid Argument");
		throw std::invalid_argument("wrong range. Check help.");
	}

	while (start_addr < end_addr) {
		int end = start_addr + ERASE_SIZE_AT_ONCE;
		if (end > end_addr) end = end_addr;

		getSSD().erase(start_addr, end - start_addr);

		start_addr += ERASE_SIZE_AT_ONCE;
	}

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Execute()");
}

const string& EraseRangeCommand::getHelp()
{
	return _HELP_MESSAGE;
}
