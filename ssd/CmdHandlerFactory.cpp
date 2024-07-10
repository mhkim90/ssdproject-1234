#include <iostream>
#include "CmdHandler.h"
#include "ReadCmdHandler.cpp"
#include "WriteCmdHandler.cpp"
#include "EraseCmdHandler.cpp"
#include "FlushCmdHandler.cpp"

class CmdHandlerFactory
{
public:
    static CmdHandlerFactory& getInstance()
    {
        static CmdHandlerFactory instance{};
        return instance;
    }

    CmdHandler* createCmdHandler(CmdOpcode opcode)
    {
        CmdHandler* cmdHandler = nullptr;
        if (opcode == READ_CMD)
        {
            cmdHandler = new ReadCmdHandler();
        }
        else if (opcode == WRITE_CMD)
        {
            cmdHandler = new WriteCmdHandler();
        }
        else if (opcode == ERASE_CMD)
        {
            cmdHandler = new EraseCmdHandler();
        }
        else if (opcode == FLUSH_CMD)
        {
            cmdHandler = new FlushCmdHandler();
        }
        return cmdHandler;
    }

private:
    CmdHandlerFactory() {}

};