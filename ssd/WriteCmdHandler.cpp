#include "WriteCmdHandler.h"

WriteCmdHandler::WriteCmdHandler() {

	CmdHandler::setOpcode(CmdOpcode::WRITE_CMD);
}

bool WriteCmdHandler::sanityCheckPassed(int lba, string data)
{
	// lba range check first
	if (true == CmdHandler::sanityCheckPassed(lba, data))
	{
		// then write command should have data as input parameter
		if (data.size() == 0) return false;

		return true;
	}
	return false;
}

void WriteCmdHandler::execute(int lba, string data)
{
	// update command buffer only
	CommandBuffer::getInstance().updateCommandBuffer(CmdHandler::getOpcode(), lba, data);

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Write Executed");
}