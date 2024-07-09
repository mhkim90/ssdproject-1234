#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../ssd/CmdHandler.h"
#include "../ssd/WriteCmdHandler.cpp"
#include "../ssd/ReadCmdHandler.cpp"
#include "../ssd/SSDManager.cpp"
#include "../ssd/CmdHandlerFactory.cpp"

using namespace std;
using namespace testing;

class MockWriteCmdHandler : public WriteCmdHandler {
public:
	MOCK_METHOD(void, execute, (int lba, string data), (override));
};

class MockReadCmdHandler : public ReadCmdHandler {
public:
	MOCK_METHOD(void, execute, (int lba, string data), (override));
};

class SSD_IO_Fixture : public testing::Test {
public:

private:

protected:
	void SetUp() override {

	}
};

TEST(SSDCommandTest, WriteTest) {
	WriteCmdHandler write;

	write.execute(80, "0x1000");
}

TEST(SSDCommandTest, MockWriteTest) {
	NiceMock<MockWriteCmdHandler> write;

	EXPECT_CALL(write, execute(80,"0x1000"))
		.Times(1);

	write.execute(80, "0x1000");
}

TEST(SSDCommandTest, ReadTest) {
	WriteCmdHandler write;
	ReadCmdHandler read;

	write.execute(80, "0x1000");
	read.execute(80,"");
}

TEST(SSDCommandTest, MockReadTest) {
	NiceMock<ReadCmdHandler> read;
	read.execute(80,"");
}

// basic write test
TEST_F(SSD_IO_Fixture, cmdHandlerCreateUsingFactoryOfWriteCmd) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(WRITE_CMD);
	SSDManager ssdManager(cmdHandler);
	ssdManager.runCommand(3, "0x12");
}


// basic read test
TEST_F(SSD_IO_Fixture, cmdHandlerCreateUsingFactoryOfReadCmd) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(READ_CMD);
	SSDManager ssdManager(cmdHandler);
	ssdManager.runCommand(3);
}

// basic write and read
TEST_F(SSD_IO_Fixture, basicReadWriteTest) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandlerForWrite = factory.createCmdHandler(WRITE_CMD);
	SSDManager ssdManagerForWrite(cmdHandlerForWrite);
	ssdManagerForWrite.runCommand(1, "0x1222222");

	CmdHandler* cmdHandlerForRead = factory.createCmdHandler(READ_CMD);
	SSDManager ssdManagerForRead(cmdHandlerForRead);
	ssdManagerForRead.runCommand(1);
}

// write test over lba 100 (0~99 is allowed)
TEST_F(SSD_IO_Fixture, checkWriteLbaRange) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(WRITE_CMD);
	SSDManager ssdManager(cmdHandler);

	EXPECT_THROW(ssdManager.runCommand(100, "0x12"), exception);
}

// read test over lba 100 (0~99 is allowed)
TEST_F(SSD_IO_Fixture, checkReadLbaRange) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(READ_CMD);
	SSDManager ssdManager(cmdHandler);

	EXPECT_THROW(ssdManager.runCommand(100), exception);
}

// write should send data together
TEST_F(SSD_IO_Fixture, wirteShouldSendDataTogether) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(WRITE_CMD);
	SSDManager ssdManager(cmdHandler);

	EXPECT_THROW(ssdManager.runCommand(3), exception);
}

// read shouldn't send data
TEST_F(SSD_IO_Fixture, dataShouldNotSendData) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(READ_CMD);
	SSDManager ssdManager(cmdHandler);

	EXPECT_THROW(ssdManager.runCommand(3, "0x12"), exception);
}

// invalid opcode test
TEST_F(SSD_IO_Fixture, checkInvalidOpcode) {
	CmdHandlerFactory factory = CmdHandlerFactory::getInstance();
	CmdHandler* cmdHandler = factory.createCmdHandler(MAX_NUM_OF_CMD);
	EXPECT_EQ(cmdHandler, nullptr);
}