#include "CommandBuffer.h"

CommandBuffer& CommandBuffer::getInstance() {
	static CommandBuffer instance;
	return instance;
}

CommandBuffer::CommandBuffer()
{
	string cmdBuf[MAX_BUFFER_COUNT];
	// open and read file first from buffer.txt to cmdBuf
	FileManager::getInstance().initFile(COMMAND_BUFFER_FILE);
	FileManager::getInstance().openFile(COMMAND_BUFFER_FILE, cmdBuf, cmdBackupCount);
	ParseCmdBuf(cmdBuf);
}

void CommandBuffer::ParseCmdBuf(string* cmdBuf)
{
	vector<string> tokens;

	for (int i = 0; i < cmdBackupCount; i++)
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

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "****** print cmd List *******");

	for (const auto& cmd : cmdList) {
		string msg = "opcode: " + to_string(cmd.opcode) + ", lba : " + to_string(cmd.lba) + ", data: " + cmd.data;
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, msg);
	}
}

// buffer.txt will be saved "[opcode] [lba] [data]" format
// [data] could be size in erase case, data in write case
void CommandBuffer::updateCommandBuffer(CmdOpcode opcode, int lba, string data)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "total command buffer pool cmd count so far: " + to_string(cmdList.size()));

	bool commandBuffered = false;

	// erase + erase case,  merge erase
	if (opcode == CmdOpcode::ERASE_CMD && !cmdList.empty()) {

		if (cmdList.back().opcode == CmdOpcode::ERASE_CMD) {
			if (cmdList.back().lba <= lba + stoi(data) - 1 && cmdList.back().lba + stoi(cmdList.back().data) - 1 >= lba) {
				int startLBA = min(cmdList.back().lba, lba);
				int endLBA = max(lba + stoi(data) - 1, cmdList.back().lba + stoi(cmdList.back().data) - 1);
				cmdList.back().lba = startLBA;
				cmdList.back().data = to_string(endLBA + 1 - startLBA);
				commandBuffered = true;
			}
		}
	}

	if (!commandBuffered) {
		// Ignore write 1
		bool writeIgnored = false;
		for (int i = 0; i < cmdList.size(); i++) {
			if (cmdList[i].opcode == CmdOpcode::WRITE_CMD && cmdList[i].lba == lba) {
				cmdList.erase(cmdList.begin() + i);
				writeIgnored = true;
			}
		}

		if (writeIgnored) {
			IoDataStruct item;
			item.opcode = opcode;
			item.lba = lba;
			item.data = data;
			cmdList.push_back(item);
			commandBuffered = true;
		}

		// Ignore write 2
		bool writeIgnored2 = false;
		int eraseRange = stoi(data);
		for (int i = 0; i < cmdList.size(); i++) {

			if (cmdList[i].opcode == CmdOpcode::WRITE_CMD && opcode == CmdOpcode::ERASE_CMD
				&& cmdList[i].lba >= lba && cmdList[i].lba < lba + eraseRange) {
				cmdList.erase(cmdList.begin() + i);
				writeIgnored2 = true;
			}
		}

		if (writeIgnored) {
			IoDataStruct item;
			item.opcode = opcode;
			item.lba = lba;
			item.data = data;
			cmdList.push_back(item);
			commandBuffered = true;
		}
	}


	if (commandBuffered == false) {
		IoDataStruct item;
		item.opcode = opcode;
		item.lba = lba;
		item.data = data;
		cmdList.push_back(item);
	}

	FileManager::getInstance().writeFile(COMMAND_BUFFER_FILE, cmdList);

	if (needFlush()) {
		flushBuffer();
	}
}

bool CommandBuffer::needFlush() {
	return cmdList.size() == MAX_BUFFER_COUNT;
}

void CommandBuffer::flushBuffer() {
	FileManager::getInstance().flushNand(cmdList);

	// init buffer
	cmdList.clear();
}

bool CommandBuffer::IsEraseLbaRangeIncluded(int findLba, int startAddr, int endAddr)
{
	for (int address = startAddr; address < endAddr; address++)
	{
		if (findLba == address)
		{
			return true;
		}
	}
	return false;
}
// if there is write data, then it returns written data
// if there is erase data, then it checks the lba is included
bool CommandBuffer::searchPassedLatestDataForRead(int lba)
{
	string data = INIT_DATA;
	bool searchResult = false;
	for (size_t i = 0; i < cmdList.size(); ++i)
	{
		if (cmdList[i].lba == lba && cmdList[i].opcode == WRITE_CMD)
		{
			data = cmdList[i].data;
			searchResult = true;
		}
		else if (cmdList[i].opcode == ERASE_CMD)
		{
			if (true == IsEraseLbaRangeIncluded(lba, cmdList[i].lba, stoi(cmdList[i].data)))
			{
				data = INIT_DATA;
				searchResult = true;
			}
		}
	}

	return (searchResult == true) ? FileManager::getInstance().updateResult(data) : false;
}

vector<IoDataStruct>& CommandBuffer::getCmdList()
{
	return cmdList;
}

