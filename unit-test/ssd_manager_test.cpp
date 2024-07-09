#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../ssd/CmdHandler.h"
#include "../ssd/SSDManager.cpp"
#include "../ssd/CmdHandlerFactory.cpp"

using namespace std;
using namespace testing;

class SSD_IO_Fixture : public testing::Test {
public:
	CmdHandler* writeCmdHandler;
	CmdHandler* readCmdHandler;

private:

protected:
	void SetUp() override 
	{
		writeCmdHandler = CmdHandlerFactory::getInstance().createCmdHandler(WRITE_CMD);
		readCmdHandler = CmdHandlerFactory::getInstance().createCmdHandler(READ_CMD);
	}
};

// basic write test
TEST_F(SSD_IO_Fixture, cmdHandlerCreateUsingFactoryOfWriteCmd) {
	SSDManager ssdManager(writeCmdHandler);
	ssdManager.runCommand(3, "0x12");
}

// basic read test
TEST_F(SSD_IO_Fixture, cmdHandlerCreateUsingFactoryOfReadCmd) {
	SSDManager ssdManager(readCmdHandler);
	ssdManager.runCommand(3);
}

// basic write and read
TEST_F(SSD_IO_Fixture, basicReadWriteTest) {
	SSDManager ssdManagerForWrite(writeCmdHandler);
	ssdManagerForWrite.runCommand(1, "0x1222222");

	SSDManager ssdManagerForRead(readCmdHandler);
	ssdManagerForRead.runCommand(1);
}

// write test over lba 100 (0~99 is allowed)
TEST_F(SSD_IO_Fixture, checkWriteLbaRange) {
	SSDManager ssdManager(writeCmdHandler);

	EXPECT_THROW(ssdManager.runCommand(100, "0x12"), exception);
}

// read test over lba 100 (0~99 is allowed)
TEST_F(SSD_IO_Fixture, checkReadLbaRange) {
	SSDManager ssdManager(readCmdHandler);

	EXPECT_THROW(ssdManager.runCommand(100), exception);
}

// write should send data together
TEST_F(SSD_IO_Fixture, wirteShouldSendDataTogether) {
	SSDManager ssdManager(writeCmdHandler);

	EXPECT_THROW(ssdManager.runCommand(3), exception);
}

// read shouldn't send data
TEST_F(SSD_IO_Fixture, dataShouldNotSendData) {
	SSDManager ssdManager(readCmdHandler);

	EXPECT_THROW(ssdManager.runCommand(3, "0x12"), exception);
}

// invalid opcode test
TEST_F(SSD_IO_Fixture, checkInvalidOpcode) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(MAX_NUM_OF_CMD);
	EXPECT_EQ(cmdHandler, nullptr);
}