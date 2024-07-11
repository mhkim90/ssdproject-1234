#include <iostream>
#include "CmdHandler.h"
#include "ReadCmdHandler.h"
#include "WriteCmdHandler.h"
#include "EraseCmdHandler.h"
#include "FlushCmdHandler.h"
#include "CmdHandlerFactory.h"

CmdHandlerFactory& CmdHandlerFactory::getInstance()
{
    static CmdHandlerFactory instance{};
    return instance;
}

CmdHandler* CmdHandlerFactory::createCmdHandler(CmdOpcode opcode)
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