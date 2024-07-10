#pragma once
#include <string>

using namespace std;

const string NANDFILE = "nand.txt";
const string RESULTFILE = "result.txt";
const string COMMAND_BUFFER_FILE = "buffer.txt";
const string INIT_DATA = "0x00000000";
const int LBA_COUNT = 100;
const int MIN_LBA = 0;
const int MAX_LBA = 99;
const int MAX_ERASE_COUNT = 10;

enum CmdOpcode
{
	READ_CMD = 1,
	WRITE_CMD = 2,
	ERASE_CMD = 3,

	LAST_CMD = ERASE_CMD,
	MAX_NUM_OF_CMD = LAST_CMD + 1,
};

struct IoDataStruct
{
	CmdOpcode opcode;
	int lba;
	string data;
};