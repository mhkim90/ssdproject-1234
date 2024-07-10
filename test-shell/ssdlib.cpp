#include "ssdlib.h"
#include <iostream>
#include <fstream>

SSDLib::SSDLib()
{
	current_path = std::filesystem::current_path();
}

SSDLib::SSDLib(const std::string& directory_path)
	: directory_path{ directory_path } {
	current_path = std::filesystem::current_path();
}

SSDLib::SSDLib(const std::string& directory_path, const std::string& app_name)
	: directory_path{ directory_path }
	, app_name{ app_name } {
	current_path = std::filesystem::current_path();
}

SSDLib::SSDLib(const std::string& directory_path, const std::string& app_name, const std::string& result_path)
	: directory_path{ directory_path }
	, app_name{ app_name }
	, result_path{ result_path } {
	current_path = std::filesystem::current_path();
}

void SSDLib::write(int addr, const std::string& value)
{
	std::string command = current_path.string() +
		directory_path + app_name + " W " +
		std::to_string(addr) + " " + value;
	system(command.c_str());
}

std::string SSDLib::read(int addr)
{
	std::string command = current_path.string() +
		directory_path + app_name + " R " +
		std::to_string(addr);
	system(command.c_str());
	return getValue(current_path.string() + result_path +
		result_name);
}

void SSDLib::erase(int addr, int size)
{
	std::string command = current_path.string() +
		directory_path + app_name + " E " +
		std::to_string(addr) + " " + std::to_string(size);
	system(command.c_str());
}

void SSDLib::flush()
{
	std::string command = current_path.string() +
		directory_path + app_name + " F ";
	system(command.c_str());
}

std::string SSDLib::getResult()
{
	return getValue(current_path.string() + result_path +
		result_name);
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
