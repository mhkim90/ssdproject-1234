#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../test-shell/ssdlib.h"

using namespace testing;

class SSDLibFixture : public ::testing::Test {
public:
	std::string path = "\\..\\x64\\Debug";
	std::string dummy_name = "\\dummy.exe";
	std::string result_path = "\\..\\dummy";
};

TEST_F(SSDLibFixture, ReadDummyTest) {
	ISSD* ssdlib = new SSDLib(path, dummy_name, result_path);
	std::string output = ssdlib->read(0);
	EXPECT_EQ(output, "0x00000000");
}

TEST_F(SSDLibFixture, WriteDummyTest) {
	ISSD* ssdlib = new SSDLib(path, dummy_name);
	ssdlib->write(0, "0x00000000");
}