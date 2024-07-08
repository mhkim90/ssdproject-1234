#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../test-shell/WriteCommand.cpp"

using namespace std;
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
	FullwriteCommand fwrCmd;
private:

protected:
	void SetUp() override {

	}
};

TEST_F(WriteCommandFixture, WriteTestNormal) {
	
	// arrange
	CommandArgs arg = { 5, "0xAAAABBBB" };

	// act
	EXPECT_CALL(ssdMock, write(5, "0xAAAABBBB"));
	wrCmd.excute(arg);

	// assert
}

TEST_F(WriteCommandFixture, WriteTestHelp) {

	// arrange

	// act

	// assert
	EXPECT_EQ("write [LBA] [data]", wrCmd.getHelp());
}

TEST_F(FullwriteCommandFixture, FullwriteTestNormal) {

	// arrange
	CommandArgs arg = { 0, "0xAAAABBBB" };

	// act
	EXPECT_CALL(ssdMock, write(_, "0xAAAABBBB"))
		.Times(100);

	fwrCmd.excute(arg);

	// assert
}

TEST_F(FullwriteCommandFixture, FullwriteTestHelp) {
	// arrange

	// act

	// assert
	EXPECT_EQ("fullwrite [LBA] [data]", fwrCmd.getHelp());
}
