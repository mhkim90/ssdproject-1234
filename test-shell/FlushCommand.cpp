#include "command.h"

class FlushCommand : public CommandBase {
	FlushCommand(ISSD& ssd)
		: CommandBase(ssd) {}

	void execute(const vector<string>& args) override
	{
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Execute()");

		verifyArgsCount(args);
		getSSD().flush();

		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Execute()");
	}

	const string& getHelp() override
	{
		return _HELP_MESSAGE;
	}

private:
	const string _HELP_MESSAGE = "Executes all commands in the Command Buffer to empty the entire buffer.\n\
		[Example] flush\n\
		[Parameter] None\n\
		[Returns] None\n";
};