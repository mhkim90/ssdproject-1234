#pragma once
#include "CmdHandler.h"
#include <iostream>
using namespace std; 

class WriteCmdHandler : public CmdHandler
{
public:
	WriteCmdHandler() {

		CmdHandler::setOpcode(CmdOpcode::WRITE_CMD);
	}

	bool sanityCheckPassed(int lba, string data) override
	{
		// lba range check first
		if (true == CmdHandler::sanityCheckPassed(lba, data))
		{
			// then write command should have data as input parameter
			if (data.size() == 0) return false;
			
			return true;
		}
	}

	void execute(int lba, string data) override
	{
		FileManager::getInstance().openNand();

		FileManager::getInstance().updateNand(lba, data);

		FileManager::getInstance().writeNand();
	}
};