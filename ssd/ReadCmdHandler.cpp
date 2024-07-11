#include "ReadCmdHandler.h"

ReadCmdHandler::ReadCmdHandler()
{ 
	CmdHandler::setOpcode(CmdOpcode::READ_CMD);
}

bool ReadCmdHandler::sanityCheckPassed(int lba, string data)
{
	// lba range check first
	if (true == CmdHandler::sanityCheckPassed(lba, data))
	{
		// then read command cannot have data as input parameter
		if (data != "") return false;

		return true;
	}
	return false;
}

void ReadCmdHandler::execute(int lba, string data)
{
	// it searches through cmdList without searching file
	// if there is write data, then it returns written data
	// if there is erase data, then it checks the lba is included
	// otherwise, read nand data and save to result file
	if (false == CommandBuffer::getInstance().searchPassedLatestDataForRead(lba))
	{

		FileManager::getInstance().openNand();

		FileManager::getInstance().readNand(lba);
	}

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Read Executed");
}