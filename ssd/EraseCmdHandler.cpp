#include "EraseCmdHandler.h"

EraseCmdHandler::EraseCmdHandler() {
	CmdHandler::setOpcode(CmdOpcode::ERASE_CMD);
}

bool EraseCmdHandler::sanityCheckPassed(int lba, string data)
{
	// lba range check first
	if (true == CmdHandler::sanityCheckPassed(lba, data))
	{
		// then write command should have data as input parameter
		if (stoi(data) > MAX_ERASE_COUNT) return false;

		return true;
	}
	return false;
}

void EraseCmdHandler::execute(int lba, string data)
{
	// update command buffer only
	CommandBuffer::getInstance().updateCommandBuffer(CmdHandler::getOpcode(), lba, data);

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Erase Executed");
}