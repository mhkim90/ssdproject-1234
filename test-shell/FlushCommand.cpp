#include "FlushCommand.h"

FlushCommand::FlushCommand(ISSD& ssd)
	: CommandBase(ssd)
	, _HELP_MESSAGE{ string{"Executes all commands in the Command Buffer to empty the entire buffer.\n\
		[Example] flush\n\
		[Parameter] None\n\
		[Returns] None\n"} }
{
}

void FlushCommand::execute(const vector<string>& args)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Flush Execute()");

	verifyArgsCount(args);
	getSSD().flush();

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Execute()");
}

const string& FlushCommand::getHelp()
{
	return _HELP_MESSAGE;
}
