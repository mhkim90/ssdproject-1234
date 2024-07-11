#pragma once
#include <string>
#include "SSDConfig.h"
#include "CmdHandler.h"
#include "Exception.h"

class SSDManager
{
public:
	SSDManager(CmdHandler* cmd) : cmdHandler(cmd) {}

	void runCommand(int lba, string data = "");

private:
	CmdHandler* cmdHandler;
};