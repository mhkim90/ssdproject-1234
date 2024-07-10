#pragma once
#include "CmdHandler.h"

class ReadCmdHandler : public CmdHandler
{
public:
	ReadCmdHandler() { CmdHandler::setOpcode(CmdOpcode::READ_CMD); };

	bool sanityCheckPassed(int lba, string data) override
	{
		// lba range check first
		if (true == CmdHandler::sanityCheckPassed(lba, data))
		{
			// then read command cannot have data as input parameter
			if (data != "") return false;

			return true;
		}
		return false;
	}

	void execute(int lba, string data) override
	{
		FileManager::getInstance().openNand();

		FileManager::getInstance().readNand(lba);
	}
};