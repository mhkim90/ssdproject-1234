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
	FullwriteCommand write{ ssdMock };
	TestApp1 testApp1{ ssdMock, read, write };

	const int LBA_MIN_VAL = 0;
	const int LBA_MAX_VAL = 99;
	const string TEST_VAL = "0xAAAABBBB";

	void fullWrite() {
		EXPECT_CALL(ssdMock, write(_, TEST_VAL))
			.Times(100);
	}

	string fullRead() {
		string expected = "";
		for (int i = LBA_MIN_VAL; i <= LBA_MAX_VAL; i++) {
			EXPECT_CALL(ssdMock, read(i))
				.Times(1)
				.WillOnce(Return(TEST_VAL));
			expected += TEST_VAL;
			expected += "\n";
		}
		return expected;
	}

private:

protected:
	void SetUp() override {

	}
};

TEST_F(TestApp1Fixture, Shell_TestApp1_Execute) {
	fullWrite();
	string expected = fullRead();

	testing::internal::CaptureStdout();
	testApp1.execute({ TEST_VAL });
	EXPECT_EQ(testing::internal::GetCapturedStdout(), expected);
}