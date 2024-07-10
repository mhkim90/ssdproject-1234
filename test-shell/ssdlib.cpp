#include <iostream>
#include <string>
#include <fstream>
#include "ssd.h"
#include <filesystem>

class SSDLib : public ISSD {
public:
	SSDLib() {
		current_path = std::filesystem::current_path();
	}

	SSDLib(const std::string& directory_path)
		: directory_path { directory_path } {
		current_path = std::filesystem::current_path();
	}

	SSDLib(const std::string& directory_path,
		const std::string& app_name)
		: directory_path{ directory_path }
		, app_name{ app_name } {
		current_path = std::filesystem::current_path();
	}

	SSDLib(const std::string& directory_path,
		const std::string& app_name,
		const std::string& result_path)
		: directory_path{ directory_path }
		, app_name{ app_name } 
		, result_path{ result_path } {
		current_path = std::filesystem::current_path();
	}

	void write(int addr, const std::string& value) override {
		std::string command = current_path.string() +
			directory_path + app_name + " W " +
			std::to_string(addr) + " " + value;
		system(command.c_str());
	}

	std::string read(int addr) override {
		std::string command = current_path.string() +
			directory_path + app_name + " R " +
			std::to_string(addr);
		system(command.c_str());
		return getValue(current_path.string() + result_path +
						result_name);
	}

	void erase(int addr, int size) override {
		std::string command = std::string(current_path) +
			directory_path + app_name + " E " +
			std::to_string(addr) + " " + std::to_string(size);
		system(command.c_str());
	}
	
	void flush() override {
		std::string command = std::string(current_path) +
			directory_path + app_name + " F ";
		system(command.c_str());
	}

	std::string getResult() override {
		return getValue(std::string(current_path) + result_path +
			result_name);
	}

private:
	std::filesystem::path current_path;
	std::string directory_path = "\\..\\x64\\Debug";
	std::string app_name = "\\ssd.exe";
	std::string result_path = "";
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