#pragma once
#ifndef interface
#define interface struct
#endif

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <regex>
#include "ssd.h"
#include "../logger/Logger.h"

using std::string;
using std::vector;


interface ICommand {
	virtual void injectSSD(ISSD& ssd) = 0;
	virtual void execute(const vector<string>& args) = 0;
	virtual const string& getHelp() = 0;
};

class CommandBase : public ICommand {
public:
	CommandBase(ISSD& ssd, int verifyArgsCount = 0);
	virtual void execute(const vector<string>& args) override = 0;
	virtual const string& getHelp() override = 0;

	virtual void injectSSD(ISSD& ssd) override;
protected:
	void verifyArgsCount(const vector<string>& args) const;
	void verifyFormatAddress(const string& arg) const;
	void verifyFormatValue(const string& arg) const;
	void verifyAddressRange(int addr) const;
	ISSD& getSSD() const;

	static constexpr int _ADDR_RANGE_MIN = 0;
	static constexpr int _ADDR_RANGE_MAX = 99;
	ILogger& logger;

private:
	ISSD& _ssd;
	const int _VERIFY_ARGS_COUNT;
};

class ScriptBase : public CommandBase {
public:
	ScriptBase(ISSD& ssd, const string& scriptName);

	virtual void execute(const vector<string>& args) override = 0;
	virtual const string& getHelp() override = 0;

protected:
	void printRun() const;
	void printResult(bool isPass);

private:
	const string _SCRIPT_NAME;
};