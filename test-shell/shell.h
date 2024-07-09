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
	virtual string waitForCommand();
	vector<string> parsingCommandStr(const string& str);
private:
	ICommandFactory& _factory;
};