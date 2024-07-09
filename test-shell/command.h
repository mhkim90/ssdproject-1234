#pragma once
#ifndef interface
#define interface struct
#endif

#include <vector>
#include <string>
#include "ssd.h"
using std::string;
using std::vector;


interface ICommand {
	virtual void injectSSD(ISSD& ssd) = 0;
	virtual void execute(const vector<string>& args) = 0;
	virtual const string& getHelp() = 0;
};