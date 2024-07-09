#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include "ssd.h"

class SSDLib : public ISSD {
public:
	SSDLib(const std::string& directory_path)
		: directory_path { directory_path } {
		GetCurrentDirectoryA(256, current_path);
	}

	SSDLib(const std::string& directory_path,
		const std::string& app_name)
		: directory_path{ directory_path }
		, app_name{ app_name } {
		GetCurrentDirectoryA(256, current_path);
	}

	SSDLib(const std::string& directory_path,
		const std::string& app_name,
		const std::string& result_path)
		: directory_path{ directory_path }
		, app_name{ app_name } 
		, result_path{ result_path } {
		GetCurrentDirectoryA(256, current_path);
	}

	void write(int addr, const std::string& value) override {
		std::string command = std::string(current_path) + 
			directory_path + app_name + " W " +
			std::to_string(addr) + " " + value;
		system(command.c_str());
	}

	std::string read(int addr) override {
		std::string command = std::string(current_path) +
			directory_path + app_name + " R " +
			std::to_string(addr);
		system(command.c_str());
		return getValue(std::string(current_path) + result_path +
						result_name);
	}

private:
	char current_path[256];
	std::string directory_path = "\\..\\x64\\Debug";
	std::string app_name = "\\ssd.exe";
	std::string result_path = directory_path;
	std::string result_name = "\\result.txt";

	std::string getValue(const std::string& result_path) {
		std::ifstream result(result_path);
		std::string value;

		if (!result.is_open()) {
			return "";
		}

		getline(result, value, '\n');

		return value;
	}
};