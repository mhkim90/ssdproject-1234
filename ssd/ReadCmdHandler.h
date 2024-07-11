#pragma once
#pragma once
#include "CmdHandler.h"

class ReadCmdHandler : public CmdHandler
{
public:
	ReadCmdHandler();

	bool sanityCheckPassed(int lba, string data) override;

	void execute(int lba, string data) override;
};