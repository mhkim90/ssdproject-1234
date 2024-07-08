#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace testing;

class SSDFixture : public ::testing::Test {
public:

private:

protected:
	void SetUp() override {

	}
};


TEST_F(SSDFixture, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}