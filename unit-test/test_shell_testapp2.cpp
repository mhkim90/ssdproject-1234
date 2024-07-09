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

	// act
	{
		InSequence seq;

		EXPECT_CALL(ssdMock, write(0, "0xAAAABBBB"))
			.Times(30);
		EXPECT_CALL(ssdMock, write(1, "0xAAAABBBB"))
			.Times(30);
		EXPECT_CALL(ssdMock, write(2, "0xAAAABBBB"))
			.Times(30);
		EXPECT_CALL(ssdMock, write(3, "0xAAAABBBB"))
			.Times(30);
		EXPECT_CALL(ssdMock, write(4, "0xAAAABBBB"))
			.Times(30);
		EXPECT_CALL(ssdMock, write(5, "0xAAAABBBB"))
			.Times(30);

		EXPECT_CALL(ssdMock, write(0, "0x12345678"));
		EXPECT_CALL(ssdMock, write(1, "0x12345678"));
		EXPECT_CALL(ssdMock, write(2, "0x12345678"));
		EXPECT_CALL(ssdMock, write(3, "0x12345678"));
		EXPECT_CALL(ssdMock, write(4, "0x12345678"));
		EXPECT_CALL(ssdMock, write(5, "0x12345678"));

		EXPECT_CALL(ssdMock, read(0));
		EXPECT_CALL(ssdMock, read(1));
		EXPECT_CALL(ssdMock, read(2));
		EXPECT_CALL(ssdMock, read(3));
		EXPECT_CALL(ssdMock, read(4));
		EXPECT_CALL(ssdMock, read(5));
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
