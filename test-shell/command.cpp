#include <regex>
#include <stdexcept>
#include "command.h"

CommandBase::CommandBase(ISSD& ssd, int verifyArgsCount)
	: _ssd{ ssd }
	, _VERIFY_ARGS_COUNT{ verifyArgsCount }
	, logger{ Logger::getInstance("shell") }
{
}

void CommandBase::injectSSD(ISSD& ssd)
{
	_ssd = ssd;
}

void CommandBase::verifyArgsCount(const vector<string>& args) const
{
	if ((int)args.size() >= _VERIFY_ARGS_COUNT) return;
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Exception: Invalid Argument");
	throw std::invalid_argument("Not enough arguments. Check help.");
}

void CommandBase::verifyFormatAddress(const string& arg) const
{
	static std::regex REGEX{ "^[0-9]+$" };
	if (std::regex_match(arg, REGEX)) return;
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Exception: Invalid Argument");
	throw std::invalid_argument("Invalid arguments. Check help.");
}

void CommandBase::verifyFormatValue(const string& arg) const
{
	static std::regex REGEX{ "^0x[0-9A-Z]{8}$" };
	if (std::regex_match(arg, REGEX)) return;
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Exception: Invalid Argument");
	throw std::invalid_argument("Invalid arguments. Check help.");
}

void CommandBase::verifyAddressRange(int addr) const
{
	if (_ADDR_RANGE_MIN <= addr && addr <= _ADDR_RANGE_MAX) return;
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Exception: Invalid Argument");
	throw std::invalid_argument("Invalid arguments. Check help.");
}

ISSD& CommandBase::getSSD() const
{
	return _ssd;
}

ScriptBase::ScriptBase(ISSD& ssd, const string& scriptName)
	: CommandBase(ssd)
	, _SCRIPT_NAME{ scriptName }
{
}

void ScriptBase::printRun() const
{
	std::cout << _SCRIPT_NAME << " --- Run...";
}

void ScriptBase::printResult(bool isPass)
{
	std::cout << (isPass ? "Pass" : "FAIL!") << std::endl;
	if (isPass) return;
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Exception: Logic Error");
	throw std::logic_error("Failed of Script!");
}

const string& ScriptBase::getScriptName()
{
	return _SCRIPT_NAME;
}
