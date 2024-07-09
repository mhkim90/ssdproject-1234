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

class CommandBase : public ICommand {
public:
	CommandBase(int verifyArgsCount = 0);

	virtual void injectSSD(ISSD& ssd) = 0;
	virtual void execute(const vector<string>& args) = 0;
	virtual const string& getHelp() = 0;

protected:
	void verifyArgsCount(const vector<string>& args) const;
	void verifyAddress(const string& arg) const;
	void verifyValue(const string& arg) const;

	const int _VERIFY_ARGS_COUNT;
};