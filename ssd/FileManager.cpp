#pragma once
#include <fstream>
#include <iostream>
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
		if (!writeFile.is_open())
			return;

		for (int i = 0; i < LBA_COUNT; i++) {
			writeFile << INIT_DATA << endl;
		}
		writeFile.close();
	}

	void openNand()
	{
		// ready to file read
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
		if (!writeFile.is_open())
			return;

		for (int i = 0; i < LBA_COUNT; i++) {
			writeFile << buf[i] << endl;
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
	
	void eraseNand(int lba, string data) {
		int range = stoi(data);
		for (int i = 0; i < range; i++) {
			buf[lba+i] = INIT_DATA;
		}
	}

private:
	FileManager() {}
	string buf[100];
};