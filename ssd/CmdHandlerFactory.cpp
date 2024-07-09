#include <iostream>
#include "CmdHandler.h"
#include "ReadCmdHandler.cpp"
#include "WriteCmdHandler.cpp"

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
        return cmdHandler;
    }

private:
    CmdHandlerFactory() {}

};