#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../logger/Logger.h"
#include "SSDConfig.h"
#include "FileManager.cpp"
#include "Exception.cpp"
#include "CommandBuffer.cpp"

using namespace std;

class CmdHandler
{
public:
	CmdHandler() {};

	virtual void execute(int lba, string data = "")
	{
		CommandBuffer::getInstance().updateCommandBuffer(opcode, lba, data);
	}

	bool IsAvailableOpcode(CmdOpcode opcode)
	{
		return (opcode == READ_CMD) || (opcode == WRITE_CMD) || (opcode == ERASE_CMD) || (opcode == FLUSH_CMD);
	}
	virtual bool sanityCheckPassed(int lba, string data)
	{
		if (false == IsAvailableOpcode(opcode))
		{
			throw InvalidOpcodeException();
		}

		return (MIN_LBA <= lba && lba < LBA_COUNT);
	}

protected:
	void setOpcode(CmdOpcode opcode)
	{
		this->opcode = opcode;
	}

	CmdOpcode getOpcode()
	{
		return this->opcode;
	}

	ILogger& logger = Logger::getInstance("ssd");

private:
	CmdOpcode opcode;
};