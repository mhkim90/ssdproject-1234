#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SSDConfig.h"
#include "FileManager.cpp"
using namespace std;

#define DEBUG_MODE 1

#define TRACE(message) \
    do { \
        if (DEBUG_MODE) { \
            std::cout << (message) << std::endl; \
        } \
    } while (0)

class CommandBuffer
{
public:
	static CommandBuffer& getInstance() {
		static CommandBuffer instance;
		return instance;
	}

	// TODO
	void ParseCmdBuf(string *cmdBuf)
	{
		vector<string> tokens;

		for (int i = 0; i < cmdCnt; i++)
		{
			std::istringstream iss(cmdBuf[i]); // Initialize iss with buf
			IoDataStruct dataStruct;
			string tempBuffer;
			iss >> tempBuffer;
			dataStruct.opcode = static_cast<CmdOpcode>(stoi(tempBuffer));
			iss >> tempBuffer;
			dataStruct.lba = stoi(tempBuffer);
			iss >> tempBuffer;
			if (dataStruct.opcode != READ_CMD)
			{
				dataStruct.data = tempBuffer;
			}

			cmdList.push_back(dataStruct);
		}

		cout << "****** print cmd List *******" << endl;
		for (const auto& cmd : cmdList) {
			std::cout << "opcode: " << cmd.opcode << ", lba : " << cmd.lba
				<< ", data: " << cmd.data << std::endl;
		}
	}

	void updateCommandBuffer(CmdOpcode opcode, int lba, string data)
	{	
		cout << "total command buffer pool cmd count : " << cmdCnt << endl;
		// buffer.txt will be saved "[opcode] [lba] [data]" format
		// [data] could be size in erase case, data in write case
		string tempBuffer = to_string(opcode) + " " + to_string(lba) + " " + data;
		FileManager::getInstance().writeFile(COMMAND_BUFFER_FILE, &tempBuffer);
		cmdCnt++;

		IoDataStruct item;
		item.opcode = opcode;
		item.lba = lba;
		item.data = data;
		cmdList.push_back(item);

		// 10개되면 flush
		//CmdBufCheckerMgr::getInstance().ArrangeBuffer();

		// E 되면 앞에꺼 scan해서 지우기
	}

	bool needFlush() {
		return cmdCnt == MAX_BUFFER_COUNT;
	}

	void flushBuffer() {
		FileManager::getInstance().flushNand(cmdList);

		// buffer 초기화
		cmdCnt = 0;
		cmdList.clear();
	}

private:
	CommandBuffer()
	{
		string cmdBuf[1000];

		// open and read file first from buffer.txt to cmdBuf
		FileManager::getInstance().initFile(COMMAND_BUFFER_FILE);
		FileManager::getInstance().openFile(COMMAND_BUFFER_FILE, cmdBuf, cmdCnt);
		ParseCmdBuf(cmdBuf);
	}
	int cmdCnt;
	vector<IoDataStruct> cmdList;
};

