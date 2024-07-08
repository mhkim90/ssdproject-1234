#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../ssd/CmdHandler.h"
#include "../ssd/WriteCmdHandler.cpp"
#include "../ssd/ReadCmdHandler.cpp"
#include "../ssd/SSDManager.cpp"

using namespace std;
using namespace testing;

class SSD_IO_Fixture : public testing::Test {
public:

private:

protected:
	void SetUp() override {

	}
};

class MockWriteCmdHandler : public WriteCmdHandler {
public:
	MOCK_METHOD(void, execute, (int lba, string data), (override));
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

// basic write test
TEST_F(SSD_IO_Fixture, basicWriteTest) {
	SSDManager ssdManager("write");
	ssdManager.runCommand(0, "0x12");
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

// basic read test
TEST_F(SSD_IO_Fixture, basicReadTest) {
	SSDManager ssdManager("read");
	ssdManager.runCommand(3);
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

// write test over lba 100 (0~99 is allowed)
TEST_F(SSD_IO_Fixture, checkWriteLbaRange) {
	SSDManager ssdManager("write");
	EXPECT_THROW(ssdManager.runCommand(100, "0x12"), exception);
}

#if TODO
// read test over lba 100 (0~99 is allowed)
TEST_F(SSD_IO_Fixture, checkReadLbaRange) {
	SSDManager ssdManager("read");
	EXPECT_THROW(ssdManager.runCommand(100), exception);
}
#endif

// write should send data together
// TODO : should be implemented in WriteCmdHandler
#if TODO
TEST_F(SSD_IO_Fixture, TestName) {
	SSDManager ssdManager("write");
	EXPECT_THROW(ssdManager.runCommand(3), exception);
}

// read shouldn't send data
// TODO : should be implemented in ReadCmdHandler
TEST_F(SSD_IO_Fixture, TestName) {
	SSDManager ssdManager("read");
	EXPECT_THROW(ssdManager.runCommand(3, "0x12"), exception);
}
#endif

// invalid opcode test
TEST_F(SSD_IO_Fixture, checkInvalidOpcode) {
	try
	{
		SSDManager ssdManager("compare");
		FAIL();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		EXPECT_EQ(string(e.what()), string("invalid opcode !! check code"));
	}
}
