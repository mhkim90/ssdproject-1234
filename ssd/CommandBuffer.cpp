#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SSDConfig.h"
#include "FileManager.cpp"
using namespace std;

class CommandBuffer
{
public:
	static CommandBuffer& getInstance() {
		static CommandBuffer instance;
		return instance;
	}

	// TODO
	void ParseCmdBuf()
	{

	}

	void updateCommandBuffer(CmdOpcode opcode, int lba, string data)
	{	
		cout << "total command bufffer pool cmd count : " << cmdCnt << endl;
		// buffer.txt will be saved "[opcode] [lba] [data]" format
		// [data] could be size in erase case, data in write case
		string tempBuffer = to_string(opcode) + " " + to_string(lba) + " " + data;
		FileManager::getInstance().writeFile(COMMAND_BUFFER_FILE, &tempBuffer);
		cmdCnt++;

		// 10개되면 flush
		//CmdBufCheckerMgr::getInstance().ArrangeBuffer();

		// E 되면 앞에꺼 scan해서 지우기
	}
private:
	CommandBuffer()
	{
		// open and read file first from buffer.txt to cmdBuf
		FileManager::getInstance().initFile(COMMAND_BUFFER_FILE);
		FileManager::getInstance().openFile(COMMAND_BUFFER_FILE, cmdBuf, cmdCnt);
		ParseCmdBuf();
	}
	string cmdBuf[1000];
	int cmdCnt;
	vector<IoDataStruct> cmdList;
};

