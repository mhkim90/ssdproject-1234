#pragma once
#include "CmdHandler.h"

class EraseCmdHandler : public CmdHandler
{
public:
	EraseCmdHandler();

	bool sanityCheckPassed(int lba, string data) override;

	void execute(int lba, string data) override;
};