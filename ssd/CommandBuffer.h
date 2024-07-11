#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SSDConfig.h"
#include "FileManager.h"

using namespace std;

class CommandBuffer
{
public:
	static CommandBuffer& getInstance();

	void ParseCmdBuf(string* cmdBuf);

	void updateCommandBuffer(CmdOpcode opcode, int lba, string data);

	bool needFlush();

	void flushBuffer();

	bool IsEraseLbaRangeIncluded(int findLba, int startAddr, int endAddr);

	// if there is write data, then it returns written data
	// if there is erase data, then it checks the lba is included
	bool searchPassedLatestDataForRead(int lba);

	vector<IoDataStruct>& getCmdList();

protected:
	ILogger& logger = Logger::getInstance("ssd");

private:
	CommandBuffer();
	CommandBuffer(const CommandBuffer&) = delete;

	int cmdBackupCount = 0;
	vector<IoDataStruct> cmdList;
};

