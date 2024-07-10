#pragma once

#include <string>
#include <stdexcept>
#include <regex>
#include "command.h"

class WriteCommand : public CommandBase {
public:
	WriteCommand(ISSD& ssd, int argsCount = 2);

	void execute(const vector<string>& args) override;

	const string& getHelp() override;

private:
	const string WRITE_HELP;
};

class FullWriteCommand : public CommandBase {
public:
	FullWriteCommand(ISSD& ssd, int argsCount = 1);

	void execute(const vector<string>& args) override;

	void writeAtAllSsdField(const std::string& value);

	const string& getHelp() override;

private:
	const string FULLWRITE_HELP;
};