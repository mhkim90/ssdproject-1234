#include "CmdHandler.h"

class SSDManager
{
	SSDManager(CmdHandler *handler)
		: cmdHandler(handler)
	{
		cmdHandler->fileOpen();
	}
	~SSDManager()
	{
		cmdHandler->fileClose();
	}
	void runCommand()
	{
		cmdHandler->execute();
	}
private:
	CmdHandler* cmdHandler;
};