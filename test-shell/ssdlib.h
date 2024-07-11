#pragma once
#include <string>
#include <filesystem>
#include "ssd.h"

class SSDLib : public ISSD {
public:
	SSDLib();
	SSDLib(const std::string& directory_path);
	SSDLib(const std::string& directory_path,
		const std::string& app_name);
	SSDLib(const std::string& directory_path,
		const std::string& app_name,
		const std::string& result_path);

	void write(int addr, const std::string& value) override;
	std::string read(int addr) override;
	void erase(int addr, int size) override;
	void flush() override;
	std::string getResult() override;

private:
	std::filesystem::path current_path;
	std::string directory_path = "\\..\\x64\\Debug";
	std::string app_name = "\\ssd.exe";
	std::string result_path = "";
	std::string result_name = "\\result.txt";

	std::string getValue(const std::string& result_path);
};