#pragma once
#include "CmdHandler.h"
#include <iostream>
using namespace std;

class EraseCmdHandler : public CmdHandler
{
public:
	EraseCmdHandler();

	bool sanityCheckPassed(int lba, string data) override;

	void execute(int lba, string data) override;
};