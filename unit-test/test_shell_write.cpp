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
	wrCmd.execute(arg);

	// assert
}

TEST_F(WriteCommandFixture, WriteTestInvalidAddress) {

	// arrange
	CommandArgs arg = { 105, "0xAAAABBBB" };

	// act
	EXPECT_THROW(wrCmd.execute(arg), std::invalid_argument);

	// assert
}

TEST_F(WriteCommandFixture, WriteTestInvalidValue) {

	// arrange
	CommandArgs arg = { 99, "0xAAAABBB*" };

	// act
	EXPECT_THROW(wrCmd.execute(arg), std::invalid_argument);

	// assert
}

TEST_F(WriteCommandFixture, WriteTestHelp) {

	// arrange
	string expectedString = "\
		LBA에 입력 Value 를 기록한다.\n\
		[Example] write [LBA] [Value]\n\
		[Parameters]\n\
		- LBA: 기록할 영역 주소값 (0~99)\n\
		- Value: 기록할 값\n\
		[Returns] 없음\n";

	// act

	// assert
	EXPECT_EQ(expectedString, wrCmd.getHelp());
}

TEST_F(FullwriteCommandFixture, FullwriteTestNormal) {

	// arrange
	CommandArgs arg = { 0, "0xAAAABBBB" };

	// act
	EXPECT_CALL(ssdMock, write(_, "0xAAAABBBB"))
		.Times(100);

	fwrCmd.execute(arg);

	// assert
}

TEST_F(FullwriteCommandFixture, FullwriteTestInvalidValue) {

	// arrange
	CommandArgs arg = { 99, "0xAAA*BBBC" };

	// act
	EXPECT_THROW(fwrCmd.execute(arg), std::invalid_argument);

	// assert
}

TEST_F(FullwriteCommandFixture, FullwriteTestHelp) {

	// arrange
	string expectedString ="\
		LBA 0 번부터 99 번 까지 Write를 수행한다.\n\
		[Example] fullwrite [any] [Value]\n\
		[Parameters]\n\
		- any\n\
		- Value: 기록할 값\n\
		[Returns] 없음\n";

	// act

	// assert
	EXPECT_EQ(expectedString, fwrCmd.getHelp());
}
