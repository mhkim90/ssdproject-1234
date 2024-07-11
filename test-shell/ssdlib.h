#pragma once
#include <string>
#include <filesystem>
#include "ssd.h"
#include "../logger/Logger.h"

class SSDLib : public ISSD {
public:
	static ISSD& getInstance();

	void write(int addr, const std::string& value) override;
	std::string read(int addr) override;
	void erase(int addr, int size) override;
	void flush() override;

protected:
	SSDLib();

private:
	std::filesystem::path current_path;
	std::string app_name = "\\ssd.exe";
	std::string result_name = "\\result.txt";
	ILogger& logger;

	virtual void execute(const std::string& command_str);
	virtual std::string getValue(const std::string& result_path);
	std::string getAppPath();
};