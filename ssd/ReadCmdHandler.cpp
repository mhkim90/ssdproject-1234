#include "CmdHandler.h"

class ReadCmdHandler : public CmdHandler
{
	// CmdHandler을(를) 통해 상속됨
	void fileOpen() override
	{
	}
	void fileClose() override
	{
	}
	void execute(int lba, string data) override
	{
	}
};