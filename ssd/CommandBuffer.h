#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include "SSDConfig.h"
#include "FileManager.h"

using namespace std;

class CommandBuffer
{
public:
	static CommandBuffer& getInstance();

	void ParseCmdBuf(string* cmdBuf);

	void updateCommandBuffer(CmdOpcode opcode, int lba, string data);

	void addCmdtoCmdList(CmdOpcode opcode, int lba, std::string& data);

	bool IsMergedWithBufferedCommands(CmdOpcode opcode, int& lba, std::string& data);

	bool checkWriteIgnorable(int i, CmdOpcode opcode, int& lba, int eraseRange);

	bool checkDuplicatedWrite(int i, int& lba);

	void updateLastEraseCmd(int lba, std::string data);

	bool ableToCombineErase(int lba, std::string data);

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

