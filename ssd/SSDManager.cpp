#include <string>
#include "SSDConfig.h"
#include "CmdHandler.h"
#include "FileManager.cpp"
#include "ReadCmdHandler.cpp"
#include "WriteCmdHandler.cpp"
#include "Exception.cpp"
using namespace std;

class SSDManager
{
public:

	SSDManager(string opcode)
	{
		if (true == IsAvailableOpcode(opcode))
		{
			if (opcode == "read") cmdHandler = new ReadCmdHandler();
			else if (opcode == "write") cmdHandler = new WriteCmdHandler();
		}
		else
		{
			throw InvalidOpcodeException();
		}
		FileManager::getInstance().initNand();
	}

	bool IsAvailableOpcode(string opcode)
	{
		return (opcode == "write") || (opcode == "read");
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