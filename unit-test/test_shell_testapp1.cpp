#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../test-shell/ssd.h"
#include "../test-shell/shell.h"
#include "../test-shell/ReadCommand.cpp"
#include "../test-shell/WriteCommand.cpp"
#include "../test-shell/TestApp1Command.cpp"

#include <iostream>
#include <string>

using namespace std;
using namespace testing;

class SSDMock : public ISSD {
public:
	MOCK_METHOD(void, write, (int addr, const string& value), (override));
	MOCK_METHOD(string, read, (int addr), (override));
};

class TestApp1Fixture : public testing::Test {
public:
	SSDMock ssdMock;
	FullReadCommand read{ ssdMock };
	FullWriteCommand write{ ssdMock };
	TestApp1Command testApp1{ ssdMock, read, write };

	const int LBA_MIN_VAL = 0;
	const int LBA_MAX_VAL = 99;
	const string TEST_VAL = "0xAAAABBBB";
	const string TEST_VAL_DIFF = "0xAAAABBBC";
	const string strHelp = "Test script1 - testapp1.\n\
		[Example] testapp1\n\
		[Parameters]\n\
		- None \n\
		[Returns] Display Pass or Fail\n";

	string fullWrite(string val) {
		string expected = "";
		for (int i = LBA_MIN_VAL; i <= LBA_MAX_VAL; i++) {
			expected += val;
			expected += "\n";
		}
		EXPECT_CALL(ssdMock, write(_, val))
			.Times(100);
		return expected;
	}

	void fullRead(string val) {
		for (int i = LBA_MIN_VAL; i <= LBA_MAX_VAL; i++) {
			EXPECT_CALL(ssdMock, read(i))
				.Times(1)
				.WillOnce(Return(val));
		}
	}

private:

protected:
	void SetUp() override {

	}
};

TEST_F(TestApp1Fixture, Shell_TestApp1_Execute_Success) {
	string expected = fullWrite(TEST_VAL);
	fullRead(TEST_VAL);

	testing::internal::CaptureStdout();
	testApp1.execute({ });
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "testapp1 --- Run...Pass\n");
}

TEST_F(TestApp1Fixture, Shell_TestApp1_Execute_Fail) {
	EXPECT_CALL(ssdMock, write(_, TEST_VAL))
		.Times(100);
	EXPECT_CALL(ssdMock, read(0))
		.Times(1)
		.WillOnce(Return(TEST_VAL_DIFF));

	testing::internal::CaptureStdout();
	testApp1.execute({ });
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "testapp1 --- Run...FAIL!\n");
}

TEST_F(TestApp1Fixture, Shell_TestApp1_GetHelp) {
	EXPECT_EQ(strHelp, testApp1.getHelp());
}