#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct DataSet {
public:
	int lba;
	string data;
};

enum CmdOpcode
{
	READ_CMD = 1,
	WRITE_CMD = 2,

	MAX_NUM_OF_CMD = WRITE_CMD + 1,
};

class CmdHandler
{
public:
	CmdHandler() {};
	virtual void fileOpen() = 0;
	virtual void fileClose() = 0;
	virtual void execute(int lba, string data ="") = 0;
	virtual bool sanityCheckPassed(int lba, string data)
	{
		return (0 <= lba && lba < 100);
	}
	const string WRITEFILENAME = "nand.txt";
	const string READFILENAME = "result.txt";

protected:
	void setOpcode(CmdOpcode opcode)
	{
		this->opcode = opcode;
	}

private:
	CmdOpcode opcode;
};