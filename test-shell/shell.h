#pragma once
#ifndef interface
#define interface struct
#endif

#include <vector>
#include "command.h"
#include "command_factory.h"

using std::vector;

interface IShell {

};

class Shell : public IShell {
public:
	Shell(ICommandFactory& factory);
	
	void run();

	virtual string waitForCommand();
	vector<string> parsingCommandStr(const string& str);
	void help();
private:
	ICommandFactory& _factory;
};