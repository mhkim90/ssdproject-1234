#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../test-shell/ssd.h"
#include "../test-shell/sheel.h"
#include "../test-shell/ReadCommand.cpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace testing;

class SSDMock : public ISSD {
public:
	MOCK_METHOD(void, write, (int addr, const string& value), (override));
	MOCK_METHOD(string, read, (int addr), (override));
};

class ReadCommandFixture : public ::testing::Test {
public:
	
private:

protected:
	void SetUp() override {

	}
};

TEST_F(ReadCommandFixture, Shell_Read_Execute) {
	SSDMock ssdMock;
	ReadCommand command{ ssdMock };
	CommandArgs args = { 3, "" };

	EXPECT_CALL(ssdMock, read(3));

	command.excute(args);
}