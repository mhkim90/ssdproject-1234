#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
#include "../test-shell/ssdlib.cpp"

using namespace testing;

TEST(SSDLibTest, ReadTest) {
	std::string path = "..\\data\\";
	ISSD* ssdlib = new SSDLib(path);
	std::string output = ssdlib->read(0);
	EXPECT_EQ(output, "0x00000000");
}