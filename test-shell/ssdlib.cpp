#include "ssdlib.h"
#include <iostream>
#include <fstream>

SSDLib::SSDLib()
	: logger(Logger::getInstance("shell"))
{
	current_path = std::filesystem::current_path();
}

ISSD& SSDLib::getInstance()
{
	static SSDLib instance;
	return instance;
}

void SSDLib::write(int addr, const std::string& value)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Write()");
	std::string command = current_path.string() +
		directory_path + app_name + " W " +
		std::to_string(addr) + " " + value;
	execute(command);
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Write()");
}

std::string SSDLib::read(int addr)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Read()");
	std::string command = current_path.string() +
		directory_path + app_name + " R " +
		std::to_string(addr);
	execute(command);
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Read()");
	return getValue(current_path.string() + result_path +
		result_name);
}

void SSDLib::erase(int addr, int size)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Erase()");
	std::string command = current_path.string() +
		directory_path + app_name + " E " +
		std::to_string(addr) + " " + std::to_string(size);
	execute(command);
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Erase()");
}

void SSDLib::flush()
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Flush()");
	std::string command = current_path.string() +
		directory_path + app_name + " F ";
	execute(command);
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Flush()");
}

std::string SSDLib::getResult()
{
	return getValue(current_path.string() + result_path +
		result_name);
}

void SSDLib::execute(const std::string& command_str)
{
	system(command_str.c_str());
}

std::string SSDLib::getValue(const std::string& result_path)
{
	std::ifstream result(result_path);
	std::string value;

	if (!result.is_open()) {
		return "";
	}

	getline(result, value, '\n');

	return value;
}
