#pragma once
#include <fstream>
#include "SSDConfig.h"

class FileManager {
public:
	static FileManager& getInstance() {
		static FileManager instance;
		return instance;
	}

	void initNand() {
		// set file as zero
		ifstream checkFile(NANDFILE);

		if (checkFile.good()) {
			checkFile.close();
			return;
		}

		ofstream writeFile;
		writeFile.open(NANDFILE);
		if (writeFile.is_open())
		{
			for (int i = 0; i < 100; i++) {
				writeFile << INIT_DATA;
			}
		}
		writeFile.close();
	}

	void openNand()
	{
		// 파일 읽기 준비
		ifstream readFile(NANDFILE);
		string tmp;

		if (!readFile.is_open()) {
			return;
		}
		int i = 0;
		while (getline(readFile, tmp, '\n')) {
			buf[i++] = tmp;
		}

		readFile.close();
	}

	void writeNand() {
		ofstream writeFile;
		writeFile.open(NANDFILE);
		if (writeFile.is_open())
		{
			for (int i = 0; i < LBA_COUNT; i++) {
				writeFile << buf[i] + "\n";
			}
		}
		writeFile.close();
	}

	void readNand(int lba) {
		ofstream resultFile;
		resultFile.open(RESULTFILE);
		if (resultFile.is_open())
		{
			resultFile << buf[lba] << endl;
		}
		resultFile.close();
	}

	void updateNand(int lba, string data) {
		buf[lba] = data;
	}

private:
	FileManager() {}
	string buf[100];
};