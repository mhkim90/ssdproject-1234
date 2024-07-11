#pragma once
#include "command.h"

class TestApp1Command : public ScriptBase {
public:
	TestApp1Command(ISSD& ssd);

	void execute(const vector<string>& args) override;

	const string& getHelp() override;

private:
	const string TEST_VAL;
	const string strHelp;
};