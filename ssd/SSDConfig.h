#pragma once
#include <string>

using namespace std;

const string NANDFILE = "nand.txt";
const string RESULTFILE = "result.txt";
const string INIT_DATA = "0x00000000\n";
const int LBA_COUNT = 100;
const int MIN_LBA = 0;
const int MAX_LBA = 99;

enum CmdOpcode
{
	READ_CMD = 1,
	WRITE_CMD = 2,

	MAX_NUM_OF_CMD = WRITE_CMD + 1,
};