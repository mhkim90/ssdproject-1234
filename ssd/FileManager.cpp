#pragma once
#include <fstream>
#include <iostream>
#include "SSDConfig.h"

using namespace std;

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

	void initFile(const string file_name) {
		// set file as zero
		ifstream checkFile(file_name);

		if (checkFile.good()) {
			checkFile.close();
			return;
		}
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

	void openFile(const string file_name, string *buf, int &cmdCnt)
	{
		cout << "open file has to be called for once" << endl;
		// ready to file read
		ifstream readFile(file_name);

		if (!readFile.is_open()) {
			return;
		}

		// save data to buf
		int buf_index = 0;
		string data;
		cmdCnt = 0;
		while (getline(readFile, data, '\n')) {
			buf[buf_index++] = data;
			cout << "openFile str :" << buf[buf_index - 1] << endl;
			cmdCnt++;
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

	void writeFile(const string file_name, string *buf) {
		cout << "writeFile is called :" << *buf << endl;
		ofstream writeFile;
		writeFile.open(file_name, std::ios::out | std::ios::app);
		if (writeFile.is_open())
		{
			writeFile << *buf << endl;
		}
		writeFile.close();
	}

	// read from nand and save it to result.txt
	void readNand(int lba) {
		ofstream resultFile;
		resultFile.open(RESULTFILE);

		if (!resultFile.is_open())
			return;

		resultFile << buf[lba] << endl;

		resultFile.close();
	}

	bool updateResult(string data) {
		ofstream resultFile;
		resultFile.open(RESULTFILE);

		if (!resultFile.is_open())
			return false;

		resultFile << data << endl;

		resultFile.close();

		return true;
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
	
	void flushNand(vector<IoDataStruct> cmdList) {
		// do flush
		openNand();
		for (auto cmd : cmdList) {
			if (cmd.opcode == WRITE_CMD) {
				updateNand(cmd.lba, cmd.data);
			}
			else if (cmd.opcode == ERASE_CMD) {
				// do erase
				eraseNand(cmd.lba, cmd.data);
			}
		}
		writeNand();
	}

private:
	FileManager() {}
	string buf[1000];
};