#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "CmdHandler.h"

using namespace std; 

class WriteCmdHandler : public CmdHandler
{
public:
	WriteCmdHandler() {

		cout << "File Init\n";

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

		if (lba >= 100 || lba < 0)
			return;

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
	}

private:
	ofstream writeFile;
	string buf[100];
};