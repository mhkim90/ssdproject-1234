#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../test-shell/WriteCommand.cpp"

using namespace testing;

class SsdMock : public ISSD {
public:
	MOCK_METHOD(void, write, (int addr, const string& value), (override));
	MOCK_METHOD(string, read, (int addr), (override));
};

class WriteCommandFixture : public ::testing::Test {
public:
	WriteCommandFixture(): wrCmd(ssdMock) {
	}

	SsdMock ssdMock; 
	WriteCommand wrCmd;
private:

protected:
	void SetUp() override {

	}
};

class FullwriteCommandFixture : public ::testing::Test {
public:
	FullwriteCommandFixture() : fwrCmd(ssdMock) {
	}

	SsdMock ssdMock;
	FullWriteCommand fwrCmd;
private:

protected:
	void SetUp() override {

	}
};

TEST_F(WriteCommandFixture, WriteTestNormal) {
	
	// arrange
	vector<string> arg = { "5", "0xAAAABBBB"};

	// act
	EXPECT_CALL(ssdMock, write(5, "0xAAAABBBB"));
	wrCmd.execute(arg);

	// assert
}

TEST_F(WriteCommandFixture, WriteTestInvalidAddress) {

	// arrange
	vector<string> arg = { "105", "0xAAAABBBB" };

	// act
	EXPECT_THROW(wrCmd.execute(arg), std::invalid_argument);

	// assert
}

TEST_F(WriteCommandFixture, WriteTestInvalidValue) {

	// arrange
	vector<string> arg = { "99", "0xAAAABBB*" };

	// act
	EXPECT_THROW(wrCmd.execute(arg), std::invalid_argument);

	// assert
}

TEST_F(WriteCommandFixture, WriteTestHelp) {

	// arrange
	string expectedString = "write Value at LBA address\n\
		[Example] write [LBA] [Value]\n\
		[Parameters]\n\
		- LBA: address (0~99)\n\
		- Value: a value to be recorded\n\
		[Returns] none\n";

	// act

	// assert
	EXPECT_EQ(expectedString, wrCmd.getHelp());
}

TEST_F(FullwriteCommandFixture, FullwriteTestNormal) {

	// arrange
	vector<string> arg = { "0xAAAABBBB" };

	// act
	EXPECT_CALL(ssdMock, write(_, "0xAAAABBBB"))
		.Times(100);

	fwrCmd.execute(arg);

	// assert
}

TEST_F(FullwriteCommandFixture, FullwriteTestInvalidValue) {

	// arrange
	vector<string> arg = { "0xAAA*BBBC" };

	// act
	EXPECT_THROW(fwrCmd.execute(arg), std::invalid_argument);

	// assert
}

TEST_F(FullwriteCommandFixture, FullwriteTestHelp) {

	// arrange
	string expectedString = "\Perform write from address 0 to 99.\n\
		[Example] fullwrite [any] [Value]\n\
		[Parameters]\n\
		- any\n\
		- Value: a value to be recorded\n\
		[Returns] none\n";

	// act

	// assert
	EXPECT_EQ(expectedString, fwrCmd.getHelp());
}
