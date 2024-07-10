#pragma once
#include "CmdHandler.h"
#include <iostream>
using namespace std;

class FlushCmdHandler : public CmdHandler
{
public:
	FlushCmdHandler() {

		CmdHandler::setOpcode(CmdOpcode::FLUSH_CMD);
	}

	bool sanityCheckPassed(int lba, string data) override
	{
		// lba range check first
		if (true == CmdHandler::sanityCheckPassed(0, "0"))
		{
			return true;
		}
		return false;
	}

	void execute(int lba, string data) override
	{
		CommandBuffer::getInstance().flushBuffer();
	}
};