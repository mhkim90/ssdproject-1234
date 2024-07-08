#pragma once
#include <string>

using namespace std;

struct DataSet {
public:
	int lba;
	string data;
};

class CmdHandler
{
public:
	CmdHandler() {};
	virtual void fileOpen() = 0;
	virtual void fileClose() = 0;
	virtual void execute(int lba, string data ="") = 0;
	const string WRITEFILENAME = "nand.txt";
	const string READFILENAME = "result.txt";
};