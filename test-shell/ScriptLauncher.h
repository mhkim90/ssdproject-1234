#pragma once
#include "command.h"

class ScriptLauncher : public ScriptBase {
public:
	ScriptLauncher(ISSD& ssd, const string& scriptName);
	virtual void execute(const vector<string>& args) override = 0;
	virtual const string& getHelp() override = 0;
};