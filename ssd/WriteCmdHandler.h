#pragma once
#pragma once
#include "CmdHandler.h"
#include <iostream>
using namespace std;

class WriteCmdHandler : public CmdHandler
{
public:
	WriteCmdHandler();

	bool sanityCheckPassed(int lba, string data) override;

	void execute(int lba, string data) override;
};