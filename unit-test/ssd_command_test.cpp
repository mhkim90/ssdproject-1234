#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../ssd/CmdHandler.h"
#include "../ssd/WriteCmdHandler.cpp"
#include "../ssd/ReadCmdHandler.cpp"

using namespace std;
using namespace testing;

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