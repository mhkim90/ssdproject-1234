#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../test-shell/ssd.h"
#include "../test-shell/shell.h"
#include "../test-shell/ReadCommand.h"

#include <iostream>
#include <string>

using namespace std;
using namespace testing;

class SSDMock : public ISSD {
public:
	MOCK_METHOD(void, write, (int addr, const string& value), (override));
	MOCK_METHOD(string, read, (int addr), (override));
	MOCK_METHOD(void, erase, (int addr, int size), (override));
	MOCK_METHOD(void, flush, (), (override));
};

class ReadCommandFixture : public ::testing::Test {
public:
	SSDMock ssdMock;
	ReadCommand command{ ssdMock };
	vector<string> normalArgs, abnormalArgs;

	const int Success_LBA = 99;
	const int Fail_LBA = 101;
	const string TEST_DATA = "0x12345678";
	const string strHelp = "Reads the value written at LBA and displays it on the screen.\n\
		[Example] read [LBA]\n\
		[Parameters]\n\
		- LBA: LBA area value to read(0~99)\n\
		[Returns] Displays the data read from LBA.\n";

private:

protected:
	void SetUp() override {
		normalArgs = { to_string(Success_LBA) };
		abnormalArgs = { to_string(Fail_LBA),  };
	}
};

class FullReadCommandFixture : public testing::Test {
public:
	SSDMock ssdMock;
	FullReadCommand command{ ssdMock };
	vector<string> normalArgs, abnormalArgs;

	const int LBA_MIN_VAL = 0;
	const int LBA_MAX_VAL = 99;
	const string strHelp = "Reads and displays values from LBA 0 to 99 on the screen.\n\
		[Example] fullread\n\
		[Parameter] None\n\
		[Returns] Displays the data read from each LBA.\n";

private:

protected:
	void SetUp() override {
		normalArgs = {  };
		abnormalArgs = {  };
	}
};

TEST_F(ReadCommandFixture, Shell_Read_Execute_Success) {
	EXPECT_CALL(ssdMock, read(Success_LBA))
		.Times(1)
		.WillRepeatedly(Return(TEST_DATA));

	testing::internal::CaptureStdout();
	command.execute(normalArgs);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), TEST_DATA + "\n");
}

TEST_F(ReadCommandFixture, Shell_Read_Execute_Fail) {
	EXPECT_THROW(command.execute(abnormalArgs), std::invalid_argument);
}

TEST_F(ReadCommandFixture, Shell_Read_GetHelp) {
	EXPECT_EQ(strHelp, command.getHelp());
}

TEST_F(ReadCommandFixture, Shell_FullRead_Invalid_Arguments_Length) {
	EXPECT_CALL(ssdMock, read)
		.Times(0);

	EXPECT_THROW(command.execute({}), invalid_argument);
}

TEST_F(FullReadCommandFixture, Shell_FullRead_Execute_Success) {
	string expected = "";
	for (int i = LBA_MIN_VAL; i <= LBA_MAX_VAL; i++) {
		string str = to_string(i);
		EXPECT_CALL(ssdMock, read(i))
			.Times(1)
			.WillOnce(Return(str));
		expected += str;
		expected += "\n";
	}
  
	testing::internal::CaptureStdout();
	command.execute(normalArgs);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), expected);
}

TEST_F(FullReadCommandFixture, Shell_FullRead_GetHelp) {
	EXPECT_EQ(strHelp, command.getHelp());
}