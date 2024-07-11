#pragma once
#include "command.h"

class EraseCommand : public CommandBase {
public:
	EraseCommand(ISSD& ssd);

	void execute(const vector<string>& args) override;

	const string& getHelp() override;

private:
	const int MIN_ERASE_SIZE;
	const int MAX_ERASE_SIZE;
	const string _HELP_MESSAGE;
};