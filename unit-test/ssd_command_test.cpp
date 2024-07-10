#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../ssd/CmdHandler.h"
#include "../ssd/WriteCmdHandler.cpp"
#include "../ssd/ReadCmdHandler.cpp"
#include "../ssd/EraseCmdHandler.cpp"
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

class COMMAND_Fixture : public testing::Test {
public:
	WriteCmdHandler write;
	ReadCmdHandler read;
	MockWriteCmdHandler mockWrite;
	MockReadCmdHandler mockRead;
private:

protected:
	void SetUp() override {

	}
};


TEST_F(COMMAND_Fixture, WriteTest) {
	write.execute(80, "0x1000");
}

TEST_F(COMMAND_Fixture, MockWriteTest) {
	EXPECT_CALL(mockWrite, execute(80,"0x1000"))
		.Times(1);

	mockWrite.execute(80, "0x1000");
}

TEST_F(COMMAND_Fixture, ReadTest) {

	write.execute(80, "0x1000");
	read.execute(80,"");
}

TEST_F(COMMAND_Fixture, MockReadTest) {
	EXPECT_CALL(mockRead, execute(_,_))
		.Times(1);

	mockRead.execute(80,"");
}