#pragma once
#include "command.h"
#include "../logger/Logger.h"

class ReadCommand : public CommandBase {
public:
	ReadCommand(ISSD& ssd);

	void execute(const vector<string>& args) override;

	const string& getHelp() override;

private:
	const string _HELP_MESSAGE;
};

class FullReadCommand : public CommandBase {
public:
	FullReadCommand(ISSD& ssd);

	void execute(const vector<string>& args) override;

	const string& getHelp() override;

private:
	const string _HELP_MESSAGE;
};