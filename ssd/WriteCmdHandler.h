#pragma once
#include "CmdHandler.h"

class WriteCmdHandler : public CmdHandler
{
public:
	WriteCmdHandler();

	bool sanityCheckPassed(int lba, string data) override;

	void execute(int lba, string data) override;
};