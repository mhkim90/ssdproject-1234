#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../ssd/CmdHandler.h"
#include "../ssd/WriteCmdHandler.cpp"
#include "../ssd/ReadCmdHandler.cpp"
#include "../ssd/CmdHandlerFactory.cpp"
#include "../ssd/SSDManager.cpp"
using namespace std;
using namespace testing;

// basic command buffer test for write
TEST(COMMNAD_BUFFER, CheckCommandBufferForWrite) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(WRITE_CMD);
	SSDManager ssdManager(cmdHandler);
	ssdManager.runCommand(3, "0x12");
}

// basic command buffer test for read
TEST(COMMNAD_BUFFER, CheckCommandBufferForRead) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(READ_CMD);
	SSDManager ssdManager(cmdHandler);
	ssdManager.runCommand(3);
}

// basic command buffer test for read
TEST(COMMNAD_BUFFER, CheckCommandBufferForFlush) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(FLUSH_CMD);
	SSDManager ssdManager(cmdHandler);
	ssdManager.runCommand(0);
}