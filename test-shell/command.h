#pragma once
#ifndef interface
#define interface struct
#endif

#include <string>
#include "ssd.h"
using std::string;

struct CommandArgs {
	int addr;
	string value;
};

interface ICommand {
	virtual void injectSSD(ISSD& ssd) = 0;
	virtual void excute(CommandArgs& args) = 0;
	virtual const string& getHelp() = 0;
};