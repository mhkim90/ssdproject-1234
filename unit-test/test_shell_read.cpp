#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../test-shell/ssd.h"
#include "../test-shell/shell.h"
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
	CommandArgs normalArgs, abnormalArgs;

	const int Success_LBA = 99;
	const int Fail_LBA = 101;
	const string TEST_DATA = "0x12345678";
	const string strHelp = "\
		LBA에 적힌 값을 읽어 화면에 출력한다.\n \
		[Example] read LBA\n \
		[Parameters]\n \
		- LBA: 값을 읽을 LBA 영역 값 (0~99)\n \
		[Returns] LBA에서 읽은 데이터를 출력합니다.\n";

private:

protected:
	void SetUp() override {
		normalArgs = { Success_LBA, "" };
		abnormalArgs = { Fail_LBA, "" };
	}
};

TEST_F(ReadCommandFixture, Shell_Read_Execute_Success) {
	EXPECT_CALL(ssdMock, read(Success_LBA))
		.Times(1)
		.WillRepeatedly(Return(TEST_DATA));

	command.excute(normalArgs);
	EXPECT_EQ(normalArgs.value, TEST_DATA);
}

TEST_F(ReadCommandFixture, Shell_Read_Execute_Fail) {
	EXPECT_THROW(command.excute(abnormalArgs), std::invalid_argument);
}

TEST_F(ReadCommandFixture, Shell_Read_GetHelp) {
	EXPECT_EQ(strHelp, command.getHelp());
}