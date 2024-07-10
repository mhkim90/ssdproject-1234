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
using std::string;
using std::vector;


interface ICommand {
	virtual void injectSSD(ISSD& ssd) = 0;
	virtual void execute(const vector<string>& args) = 0;
	virtual const string& getHelp() = 0;
};

class CommandBase : public ICommand {
public:
	CommandBase(ISSD& ssd, int verifyArgsCount = 0)
		: _ssd{ ssd }
		, _VERIFY_ARGS_COUNT{ verifyArgsCount }
	{
	}
	virtual void execute(const vector<string>& args) override = 0;
	virtual const string& getHelp() override = 0;

	virtual void injectSSD(ISSD& ssd) override {
		_ssd = ssd;
	}
protected:
	inline void verifyArgsCount(const vector<string>& args) const {
		if ((int)args.size() >= _VERIFY_ARGS_COUNT) return;
		throw std::invalid_argument("Not enough arguments. Check help.");
	}
	inline void verifyFormatAddress(const string& arg) const {
		static std::regex REGEX{ "^[0-9]+$" };
		if (std::regex_match(arg, REGEX)) return;
		throw std::invalid_argument("Invalid arguments. Check help.");
	}
	inline void verifyFormatValue(const string& arg) const {
		static std::regex REGEX{ "^0x[A-Z]{8}$" };
		if (std::regex_match(arg, REGEX)) return;
		throw std::invalid_argument("Invalid arguments. Check help.");
	}
	inline void verifyAddressRange(int addr) const {
		if (_ADDR_RANGE_MIN <= addr && addr <= _ADDR_RANGE_MAX) return;
		throw std::invalid_argument("Invalid arguments. Check help.");
	}
	inline ISSD& getSSD() const {
		return _ssd;
	}

	static constexpr int _ADDR_RANGE_MIN = 0;
	static constexpr int _ADDR_RANGE_MAX = 99;

private:
	ISSD& _ssd;
	const int _VERIFY_ARGS_COUNT;
};

class ScriptBase : public CommandBase {
public:
	ScriptBase(ISSD& ssd, const string& scriptName)
		: CommandBase(ssd) {

	}

	virtual void execute(const vector<string>& args) override = 0;
	virtual const string& getHelp() override = 0;

protected:
	inline void printRun() const {
		std::cout << _SCRIPT_NAME << " --- Run...";
	}

	inline void printResult(bool isPass) const {
		std::cout << (isPass ? "Pass" : "FAIL!") << std::endl;
		if (isPass) return;
		throw std::logic_error("Faild of Script!");
	}

private:
	const string _SCRIPT_NAME;
};