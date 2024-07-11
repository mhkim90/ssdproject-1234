#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../test-shell/ssdlib.h"

using namespace testing;

class MockSSDLib : public SSDLib {
public:
	static MockSSDLib& getInstanceMock() {
		static MockSSDLib instance;
		return instance;
	}
	MOCK_METHOD(void, execute, (const std::string&), (override));
};

class SSDLibFixture : public ::testing::Test {
public:
	MockSSDLib& mockSSD = MockSSDLib::getInstanceMock();

protected:
	void SetUp() override {
		EXPECT_CALL(mockSSD, execute(_))
			.Times(1);

		std::ofstream resultFile("result.txt");
		resultFile << "0x00000000\n";
		resultFile.close();
	}
};

TEST_F(SSDLibFixture, READ_TEST) {
	EXPECT_EQ(mockSSD.read(0), "0x00000000");
}

TEST_F(SSDLibFixture, WRITE_TEST) {
	EXPECT_NO_THROW(mockSSD.write(0, "0x00000000"));
}