#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../test-shell/EraseRangeCommand.cpp"

using namespace testing;

class SsdMock : public ISSD {
public:
	MOCK_METHOD(void, write, (int addr, const string& value), (override));
	MOCK_METHOD(string, read, (int addr), (override));
	MOCK_METHOD(void, erase, (int addr, int size), (override));
	MOCK_METHOD(void, flush, (), (override));
	MOCK_METHOD(string, getResult, (), (override));
};

class EraseRangeCommandFixture : public ::testing::Test {
public:
	EraseRangeCommandFixture() : erCmd(ssdMock) {
	}

	SsdMock ssdMock;
	EraseRangeCommand erCmd;
private:

protected:
	void SetUp() override {

	}
};


TEST_F(EraseRangeCommandFixture, EraseRangeTestNormal1) {

	// arrange
	vector<string> arg = { "0", "4" };

	// act
	EXPECT_CALL(ssdMock, erase(0, 4));
	erCmd.execute(arg);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestNormal2) {

	// arrange
	vector<string> arg = { "5", "7" };

	// act
	EXPECT_CALL(ssdMock, erase(5, 2));
	erCmd.execute(arg);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestNormal3) {

	// arrange
	vector<string> arg = { "8", "9" };

	// act
	EXPECT_CALL(ssdMock, erase(8, 1));
	erCmd.execute(arg);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestNormal4) {

	// arrange
	vector<string> arg = { "0", "15" };

	// act
	{
		InSequence seq;
		EXPECT_CALL(ssdMock, erase(0, 10));
		EXPECT_CALL(ssdMock, erase(10, 5));
	}

	erCmd.execute(arg);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestNormal5) {

	// arrange
	vector<string> arg = { "10", "45" };

	// act
	{
		InSequence seq;
		EXPECT_CALL(ssdMock, erase(10, 10));
		EXPECT_CALL(ssdMock, erase(20, 10));
		EXPECT_CALL(ssdMock, erase(30, 10));
		EXPECT_CALL(ssdMock, erase(40, 5));
	}

	erCmd.execute(arg);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestNormal6) {

	// arrange
	vector<string> arg = { "98", "100" };

	EXPECT_CALL(ssdMock, erase(98, 2));

	erCmd.execute(arg);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestNormal7) {

	// arrange
	vector<string> arg = { "98", "103" };

	EXPECT_CALL(ssdMock, erase(98, 2));

	erCmd.execute(arg);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestNormal8) {

	// arrange
	vector<string> arg = { "0", "100" };

	// act
	{
		InSequence seq;
		EXPECT_CALL(ssdMock, erase(0, 10));
		EXPECT_CALL(ssdMock, erase(10, 10));
		EXPECT_CALL(ssdMock, erase(20, 10));
		EXPECT_CALL(ssdMock, erase(30, 10));
		EXPECT_CALL(ssdMock, erase(40, 10));
		EXPECT_CALL(ssdMock, erase(50, 10));
		EXPECT_CALL(ssdMock, erase(60, 10));
		EXPECT_CALL(ssdMock, erase(70, 10));
		EXPECT_CALL(ssdMock, erase(80, 10));
		EXPECT_CALL(ssdMock, erase(90, 10));
	}

	erCmd.execute(arg);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestFailure1) {

	// arrange
	vector<string> arg = { "0", "0" };

	// act
	EXPECT_THROW(erCmd.execute(arg), invalid_argument);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestFailure2) {

	// arrange
	vector<string> arg = { "100", "101" };

	// act
	EXPECT_THROW(erCmd.execute(arg), invalid_argument);

	// assert
}

TEST_F(EraseRangeCommandFixture, EraseRangeTestHelp) {

	// arrange
	string expectedString = "Delete a specific range of SSD.\n\
		[Example] erase START_LBA END_LBA\n\
		[Parameters]\n\
		- START_LBA: Start-address to delete(0~99)\n\
		- END_LBA: End-address to delete(1~100)\n\
		[Returns] None\n";

	// act

	// assert
	EXPECT_EQ(expectedString, erCmd.getHelp());
}
