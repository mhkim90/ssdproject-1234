#pragma once
#include "CmdHandler.h"

class ReadCmdHandler : public CmdHandler
{
public:
	ReadCmdHandler() {};

	// CmdHandler을(를) 통해 상속됨
	void execute(int lba, string data) override
	{
		fileOpen();

		readFile.open(READFILENAME);

		readFile << buf[lba] << endl;

		fileClose();

	}

	void fileOpen() override
	{
		// 파일 읽기 준비
		std::ifstream in(WRITEFILENAME);
		string tmp;

		if (!in.is_open()) {
			std::cout << "파일을 찾을 수 없습니다!" << std::endl;
			return;
		}
		int i = 0;
		while (getline(in, tmp, '\n')) {
			buf[i++] = tmp;
		}

		in.close();
	}
	void fileClose() override
	{
		readFile.close();
	}
	bool sanityCheckPassed(int lba, string data) override
	{
		return true;
	}
private:
	ofstream readFile;
	string buf[100];
};