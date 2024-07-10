#pragma once
#include "command.h"

class FlushCommand : public CommandBase {
public:
	FlushCommand(ISSD& ssd);

	void execute(const vector<string>& args) override;

	const string& getHelp() override;

private:
	const string _HELP_MESSAGE;
};