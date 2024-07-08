#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../test-shell/ssd.h"
#include "../test-shell/sheel.h"
#include "../test-shell/ReadCommand.cpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace testing;

class SSDMock : public ISSD {
public:
	MOCK_METHOD(void, write, (int addr, const string& value), (override));
	MOCK_METHOD(string, read, (int addr), (override));
};

class ReadCommandFixture : public ::testing::Test {
public:
	SSDMock ssdMock;
	ReadCommand command{ ssdMock };
	CommandArgs args;

	const int TEST_LBA = 99;
	const string TEST_DATA = "0x12345678";

private:

protected:
	void SetUp() override {
		args = { TEST_LBA, "" };
	}
};

TEST_F(ReadCommandFixture, Shell_Read_Execute) {
	EXPECT_CALL(ssdMock, read(TEST_LBA))
		.Times(1)
		.WillRepeatedly(Return(TEST_DATA));

	command.excute(args);
	EXPECT_EQ(args.value, TEST_DATA);
}