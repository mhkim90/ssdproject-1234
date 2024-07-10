#pragma once
#include <string>
#include <stdexcept>
#include <regex>
#include "command.h"

class TestApp2Command : public ScriptBase {
public:
	TestApp2Command(ISSD& ssd);

	void execute(const vector<string>& args) override;

	const string& getHelp() override;

private:
	const string WRITE_HELP;
	const int WRITE_TRY_MAX;
	const int START_LBA_FOR_AGING;
	const int END_LBA_FOR_AGING;
};
