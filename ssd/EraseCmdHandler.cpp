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
		// update command buffer only
		CommandBuffer::getInstance().updateCommandBuffer(CmdHandler::getOpcode(), lba, data);

		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Erase Executed");
	}
};