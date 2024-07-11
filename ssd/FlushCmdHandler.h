#pragma once
#pragma once
#include "CmdHandler.h"
#include <iostream>
using namespace std;

class FlushCmdHandler : public CmdHandler
{
public:
	FlushCmdHandler();

	bool sanityCheckPassed(int lba, string data) override;

	void execute(int lba, string data) override;
};