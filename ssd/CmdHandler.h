#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "SSDConfig.h"
#include "FileManager.cpp"

using namespace std;

enum CmdOpcode
{
	READ_CMD = 1,
	WRITE_CMD = 2,

	MAX_NUM_OF_CMD = WRITE_CMD + 1,
};

class CmdHandler
{
public:
	CmdHandler() {};
	virtual void execute(int lba, string data ="") = 0;
	virtual bool sanityCheckPassed(int lba, string data)
	{
		return (MIN_LBA <= lba && lba < LBA_COUNT);
	}

protected:
	void setOpcode(CmdOpcode opcode)
	{
		this->opcode = opcode;
	}

private:
	CmdOpcode opcode;
};