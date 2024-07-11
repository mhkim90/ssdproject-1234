#include "WriteCommand.h"

WriteCommand::WriteCommand(ISSD& ssd, int argsCount)
	: CommandBase(ssd, argsCount)
	, WRITE_HELP{ string{"write Value at LBA address\n\
		[Example] write [LBA] [Value]\n\
		[Parameters]\n\
		- LBA: address (0~99)\n\
		- Value: a value to be recorded\n\
		[Returns] none\n"} }
{
}

void WriteCommand::execute(const vector<string>& args)
{
	verifyArgsCount(args);

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Write " + args[0] + " " + args[1] + " Execute()");
	verifyFormatAddress(args[0]);
	verifyFormatValue(args[1]);

	int addr = stoi(args[0]);
	const std::string& value = args[1];

	verifyAddressRange(addr);

	getSSD().write(addr, value);

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Execute()");
}

const string& WriteCommand::getHelp()
{
	return WRITE_HELP;
}

FullWriteCommand::FullWriteCommand(ISSD& ssd, int argsCount)
	: CommandBase(ssd, argsCount)
	, FULLWRITE_HELP{ string{"Perform write from address 0 to 99.\n\
		[Example] fullwrite [Value]\n\
		[Parameters]\n\
		- Value: a value to be recorded\n\
		[Returns] none\n"} }
{
}

void FullWriteCommand::execute(const vector<string>& args)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start FullWrite " + args[0] + " Execute()");

	verifyArgsCount(args);

	const std::string& value = args[0];
	verifyFormatValue(value);

	writeAtAllSsdField(value);
}

void FullWriteCommand::writeAtAllSsdField(const std::string& value)
{
	for (int addr = _ADDR_RANGE_MIN; addr <= _ADDR_RANGE_MAX; addr++) {
		getSSD().write(addr, value);
	}
}

const string& FullWriteCommand::getHelp()
{
	return FULLWRITE_HELP;
}