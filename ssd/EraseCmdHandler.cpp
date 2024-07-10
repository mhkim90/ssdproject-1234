#pragma once
#include "CmdHandler.h"
#include <iostream>
using namespace std;

class EraseCmdHandler : public CmdHandler
{
public:
	EraseCmdHandler() {
		CmdHandler::setOpcode(CmdOpcode::ERASE_CMD);
	}

	bool sanityCheckPassed(int lba, string data) override
	{
		// lba range check first
		if (true == CmdHandler::sanityCheckPassed(lba, data))
		{
			// then write command should have data as input parameter
			if (stoi(data) > MAX_ERASE_COUNT) return false;

			return true;
		}
		return false;
	}

	void execute(int lba, string data) override
	{
		FileManager::getInstance().openNand();

		FileManager::getInstance().eraseNand(lba, data);

		FileManager::getInstance().writeNand();
	}
};