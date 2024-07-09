#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include "ssd.h"

class SSDLib : public ISSD {
public:
	SSDLib(const std::string& directory_path)
		: directory_path { directory_path } {}

	void write(int addr, const std::string& value) override {
		std::string command = directory_path + "\\" + app_name + " W " + 
			std::to_string(addr) + " " + value;
		ShellExecuteA(NULL, "open", command.c_str(), NULL, NULL, 0);
	}

	std::string read(int addr) override {
		std::string command = directory_path + "\\" + app_name + " R " + 
			std::to_string(addr);
		ShellExecuteA(NULL, "open", command.c_str(), NULL, NULL, 0);
		return getValue(directory_path + "\\" + result_name);
	}

	void setSSDApp(const std::string& app_name) {
		this->app_name = app_name;
	}

	void setResultName(const std::string& result_name) {
		this->result_name = result_name;
	}

private:
	std::string directory_path;
	std::string app_name = "ssd.exe";
	std::string result_name = "result.txt";

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