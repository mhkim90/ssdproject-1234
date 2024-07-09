#include <regex>
#include <stdexcept>
#include "command.h"

CommandBase::CommandBase(int verifyArgsCount)
	: _VERIFY_ARGS_COUNT{ verifyArgsCount }
{
}

void CommandBase::verifyArgsCount(const vector<string>& args) const
{
	if ((int)args.size() < _VERIFY_ARGS_COUNT) throw std::invalid_argument("Not enough arguments. Check help.");
}

void CommandBase::verifyAddress(const string& arg) const
{
	static std::regex REGEX{ "^[0-9]$" };
	if (std::regex_match(arg, REGEX)) return;
	throw std::invalid_argument("Invalid arguments. Check help.");
}

void CommandBase::verifyValue(const string& arg) const
{
	static std::regex REGEX{ "^0x[A-Z]{8}$" };
	if (std::regex_match(arg, REGEX)) return;
	throw std::invalid_argument("Invalid arguments. Check help.");
}
