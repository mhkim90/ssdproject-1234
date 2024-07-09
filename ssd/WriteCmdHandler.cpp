#pragma once
#include "CmdHandler.h"
#include <string>
#include <iostream>
using namespace std; 

class WriteCmdHandler : public CmdHandler
{
public:
	WriteCmdHandler() {

		CmdHandler::setOpcode(CmdOpcode::WRITE_CMD);

		cout << "File Init\n";

		initFile();
	}

	bool sanityCheckPassed(int lba, string data) override
	{
		// lba range check first
		if (true == CmdHandler::sanityCheckPassed(lba, data))
		{
			// then write command should have data as input parameter
			if (data.size() == 0) return false;
			
			return true;
		}
	}

	// set file as zero
	void initFile()
	{
		writeFile.open(WRITEFILENAME);
		string tmp = "0x00000000\n";
		if (writeFile.is_open())
		{
			for (int i = 0; i < 100; i++) {
				writeFile << "0x00000000\n";
			}
		}

		writeFile.close();
	}

	// CmdHandler을(를) 통해 상속됨
	void execute(int lba, string data) override
	{
		fileOpen();

		buf[lba] = data;

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
		while (getline(in, tmp, '\n')){
			buf[i++] = tmp;
		}

		in.close();
	}

	void fileClose() override
	{
		writeFile.open(WRITEFILENAME);
		if (writeFile.is_open())
		{
			for (int i = 0; i < 100; i++) {
				writeFile.write((buf[i] + "\n").c_str(), (buf[i] + "\n").size());
			}
		}

		cout << "File Close\n";

		writeFile.close();
	}

private:
	ofstream writeFile;
	string buf[100];
};