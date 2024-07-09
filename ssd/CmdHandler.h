#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "SSDConfig.h"
#include "FileManager.cpp"
#include "Exception.cpp"

using namespace std;

class CmdHandler
{
public:
	CmdHandler() {};
	virtual void execute(int lba, string data ="") = 0;
	bool IsAvailableOpcode(CmdOpcode opcode)
	{
		return (opcode == READ_CMD) || (opcode == WRITE_CMD);
	}
	virtual bool sanityCheckPassed(int lba, string data)
	{
		if (false == IsAvailableOpcode(opcode))
		{
			throw InvalidOpcodeException();
		}

		FileManager::getInstance().initNand();

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