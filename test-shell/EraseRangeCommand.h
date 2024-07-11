#pragma once
#include <string>
#include <stdexcept>
#include "command.h"

class EraseRangeCommand : public CommandBase {
public:
	EraseRangeCommand(ISSD& ssd, int argsCount = 2);

	void execute(const vector<string>& args) override;

	const string& getHelp() override;

private:
	const string _HELP_MESSAGE;

	const int ERASE_SIZE_AT_ONCE;
	const int ERASE_END_LBA;
};
