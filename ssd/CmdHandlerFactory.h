#pragma once
#include "CmdHandler.h"
#include "ReadCmdHandler.h"
#include "WriteCmdHandler.h"
#include "EraseCmdHandler.h"
#include "FlushCmdHandler.h"

class CmdHandlerFactory
{
public:
    static CmdHandlerFactory& getInstance();

    CmdHandler* createCmdHandler(CmdOpcode opcode);

private:
    CmdHandlerFactory() {}
    CmdHandlerFactory(const CmdHandlerFactory&) = delete;
};