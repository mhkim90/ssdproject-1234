#include <regex>
#include <stdexcept>
#include "command.h"
//
//CommandBase::CommandBase(ISSD& ssd, const string&  helpMsg, int verifyArgsCount)
//	: _ssd { ssd }
//	, _HELP_MSG { helpMsg }
//	, _VERIFY_ARGS_COUNT { verifyArgsCount }
//{
//}
//
//void CommandBase::injectSSD(ISSD& ssd)
//{
//	_ssd = ssd;
//}
//
//const string& CommandBase::getHelp()
//{
//	return _HELP_MSG;
//}
//
//void CommandBase::verifyArgsCount(const vector<string>& args) const
//{
//	if ((int)args.size() < _VERIFY_ARGS_COUNT) throw std::invalid_argument("Not enough arguments. Check help.");
//}
//
//void CommandBase::verifyFormatAddress(const string& arg) const
//{
//	static std::regex REGEX{ "^[0-9]$" };
//	if (std::regex_match(arg, REGEX)) return;
//	throw std::invalid_argument("Invalid arguments. Check help.");
//}
//
//void CommandBase::verifyFormatValue(const string& arg) const
//{
//	static std::regex REGEX{ "^0x[A-Z]{8}$" };
//	if (std::regex_match(arg, REGEX)) return;
//	throw std::invalid_argument("Invalid arguments. Check help.");
//}
//
//inline void CommandBase::verifyAddressRange(int addr) const
//{
//	if (ADDR_RANGE_MIN <= addr && addr <= ADDR_RANGE_MAX) return;
//	throw std::invalid_argument("Invalid arguments. Check help.");
//}
//
//ISSD& CommandBase::getSSD() const
//{
//	return _ssd;
//}
