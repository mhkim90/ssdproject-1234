#include <string>
#include "SSDConfig.h"
#include "CmdHandler.h"
#include "FileManager.cpp"
#include "ReadCmdHandler.cpp"
#include "WriteCmdHandler.cpp"
#include "EraseCmdHandler.cpp"
#include "Exception.cpp"
using namespace std;

class SSDManager
{
public:
	SSDManager(CmdHandler *cmd) : cmdHandler(cmd)
	{
	}

	void runCommand(int lba, string data = "")
	{
		if (true == cmdHandler->sanityCheckPassed(lba, data))
		{
			cmdHandler->execute(lba, data);
		}
		else
		{
			throw LbaRangeOverException();
		}
	}

private:
	CmdHandler *cmdHandler;
};