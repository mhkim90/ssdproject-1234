#include "SSDManager.h"
#include "CmdHandlerFactory.h"

int main(int argc, char* argv[])
{
    vector<string> arguments;

    if (argc > 1) {
        for (int i = 1; i < argc; i++)
        {
            arguments.push_back(argv[i]);
        }

        FileManager::getInstance().initNand();

        CmdHandlerFactory& factory = CmdHandlerFactory::getInstance();

        if (*argv[1] == 'R' || *argv[1] == 'r')
        {
            CmdHandler* cmdHandler = factory.createCmdHandler(READ_CMD);
            SSDManager ssdManager(cmdHandler);
            ssdManager.runCommand(stoi(argv[2]));
        }
        else if (*argv[1] == 'W' || *argv[1] == 'w')
        {
            CmdHandler* cmdHandler = factory.createCmdHandler(WRITE_CMD);
            SSDManager ssdManager(cmdHandler);
            ssdManager.runCommand(stoi(argv[2]), argv[3]);
        }
        else if (*argv[1] == 'E' || *argv[1] == 'e')
        {
            CmdHandler* cmdHandler = factory.createCmdHandler(ERASE_CMD);
            SSDManager ssdManager(cmdHandler);
            ssdManager.runCommand(stoi(argv[2]), argv[3]);
        }
        else if (*argv[1] == 'F' || *argv[1] == 'f')
        {
            CmdHandler* cmdHandler = factory.createCmdHandler(FLUSH_CMD);
            SSDManager ssdManager(cmdHandler);
            ssdManager.runCommand(stoi(argv[2]), argv[3]);
        }
    }
}