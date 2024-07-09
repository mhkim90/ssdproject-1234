#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../test-shell/TestApp2Command.cpp"

using namespace testing;

class SsdMock : public ISSD {
public:
	MOCK_METHOD(void, write, (int addr, const string& value), (override));
	MOCK_METHOD(string, read, (int addr), (override));
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

TEST_F(TestApp2Fixture, TestApp2TestNormal) {

	// arrange
	CommandArgs arg = { 0, "" };
	const int START_LBA = 0;
	const int END_LBA = 5;

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
			EXPECT_CALL(ssdMock, read(lba));
		}
	}

	ta2Cmd.execute(arg);

	// assert
}

TEST_F(TestApp2Fixture, TestApp2TestHelp) {

	// arrange
	string expectedString = "\
		Test script2 - testapp2. \n\
		[Example] testapp2\n\
		[Parameters]\n\
		- 없음 \n\
		[Returns] 없음\n";

	// act

	// assert
	EXPECT_EQ(expectedString, ta2Cmd.getHelp());
}
