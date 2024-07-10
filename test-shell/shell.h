#pragma once
#ifndef interface
#define interface struct
#endif

#include <vector>
#include "command.h"
#include "command_factory.h"

using std::vector;

class Shell {
public:
	Shell(ICommandFactory& factory);
	
	void run();

	virtual string waitForCommand();
	vector<string> parsingCommandStr(const string& str);
	void help();
private:
	ICommandFactory& _factory;
};