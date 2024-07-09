#include "CmdHandler.h"
#include "ReadCmdHandler.cpp"
#include "WriteCmdHandler.cpp"
#include <string>
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
	}
	bool IsAvailableOpcode(string opcode)
	{
		return (opcode == "write") || (opcode == "read");
	}
	SSDManager(CmdHandler *handler)
		: cmdHandler(handler)
	{
		cmdHandler->fileOpen();
	}
	~SSDManager()
	{
		cmdHandler->fileClose();
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