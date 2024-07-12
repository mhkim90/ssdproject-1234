#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../test-shell/TestApp2Command.h"

using namespace testing;

class SsdMock : public ISSD {
public:
	MOCK_METHOD(void, write, (int addr, const string& value), (override));
	MOCK_METHOD(string, read, (int addr), (override));
	MOCK_METHOD(void, erase, (int addr, int size), (override));
	MOCK_METHOD(void, flush, (), (override));
};

class TestApp2Fixture : public ::testing::Test {
public:
	TestApp2Fixture() : ta2Cmd(ssdMock) {
	}

	SsdMock ssdMock;
	TestApp2Command ta2Cmd;
private:

protected:
	void SetUp() override {

	}
};

TEST_F(TestApp2Fixture, TestApp2TestSuccess) {

	// arrange
	std::vector<string> arg = { "0", "" };
	const int START_LBA = 0;
	const int END_LBA = 5;

	testing::internal::CaptureStdout();

	// act
	{
		InSequence seq;
		for (int lba = START_LBA; lba <= END_LBA; lba++) {
			EXPECT_CALL(ssdMock, write(lba, "0xAAAABBBB"))
				.Times(30);
		}
		
		for (int lba = START_LBA; lba <= END_LBA; lba++) {
			EXPECT_CALL(ssdMock, write(lba, "0x12345678"));
		}

		for (int lba = START_LBA; lba <= END_LBA; lba++) {
			EXPECT_CALL(ssdMock, read(lba))
				.WillRepeatedly(Return("0x12345678"));
		}

		EXPECT_CALL(ssdMock, flush());
	}

	ta2Cmd.execute(arg);

	// assert
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "testapp2 --- Run...Pass\n");
}


TEST_F(TestApp2Fixture, TestApp2TestFailure) {

	// arrange
	std::vector<string> arg = { "0", "" };
	const int START_LBA = 0;
	const int END_LBA = 5;

	testing::internal::CaptureStdout();

	// act
	{
		InSequence seq;
		for (int lba = START_LBA; lba <= END_LBA; lba++) {
			EXPECT_CALL(ssdMock, write(lba, "0xAAAABBBB"))
				.Times(30);
		}

		for (int lba = START_LBA; lba <= END_LBA; lba++) {
			EXPECT_CALL(ssdMock, write(lba, "0x12345678"));
		}

		for (int lba = START_LBA; lba <= END_LBA; lba++) {
			EXPECT_CALL(ssdMock, read(lba))
				.WillRepeatedly(Return("0xCCCCFFFF"));
		}
	}

	try {
		ta2Cmd.execute(arg);
	}
	catch (std::logic_error&) {
		// assert
		EXPECT_EQ(testing::internal::GetCapturedStdout(), "testapp2 --- Run...FAIL!\n");
	}
}

TEST_F(TestApp2Fixture, TestApp2TestHelp) {

	// arrange
	string expectedString = "Test script2 - testapp2. \n\
		[Example] testapp2\n\
		[Parameters]\n\
		- none \n\
		[Returns] result SUCCESS/FAIL\n";

	// act

	// assert
	EXPECT_EQ(expectedString, ta2Cmd.getHelp());
}
