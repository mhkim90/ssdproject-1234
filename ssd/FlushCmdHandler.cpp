#include "FlushCmdHandler.h"

FlushCmdHandler::FlushCmdHandler() {

	CmdHandler::setOpcode(CmdOpcode::FLUSH_CMD);
}

bool FlushCmdHandler::sanityCheckPassed(int lba, string data)
{
	// lba range check first
	if (true == CmdHandler::sanityCheckPassed(0, "0"))
	{
		return true;
	}
	return false;
}

void FlushCmdHandler::execute(int lba, string data)
{
	CommandBuffer::getInstance().flushBuffer();

	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Flush Executed");
}