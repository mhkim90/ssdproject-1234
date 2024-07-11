#pragma once
#include "CmdHandler.h"

class FlushCmdHandler : public CmdHandler
{
public:
	FlushCmdHandler();

	bool sanityCheckPassed(int lba, string data) override;

	void execute(int lba, string data) override;
};