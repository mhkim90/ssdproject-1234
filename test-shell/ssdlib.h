#pragma once
#include <string>
#include <filesystem>
#include "ssd.h"

class SSDLib : public ISSD {
public:
	static ISSD& getInstance();

	void write(int addr, const std::string& value) override;
	std::string read(int addr) override;
	void erase(int addr, int size) override;
	void flush() override;
	std::string getResult() override;

protected:
	SSDLib();

private:
	std::filesystem::path current_path;
	std::string directory_path = "\\..\\x64\\Debug";
	std::string app_name = "\\ssd.exe";
	std::string result_path = "";
	std::string result_name = "\\result.txt";

	virtual void execute(const std::string& command_str);
	virtual std::string getValue(const std::string& result_path);
};