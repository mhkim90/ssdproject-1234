#pragma once
#include <fstream>
#include <iostream>
#include "SSDConfig.h"

using namespace std;

class FileManager {
public:
	static FileManager& getInstance();

	void initNand();

	void openNand();

	void writeNand();

	void writeFile(const string file_name, vector<IoDataStruct> cmdList);

	// read from nand and save it to result.txt
	void readNand(int lba);

	bool updateResult(string data);

	void updateNand(int lba, string data);

	void eraseNand(int lba, string data);

	void flushNand(vector<IoDataStruct> cmdList);

	void openFile(const string file_name, string* buf, int& cmdBackupCount);

	void initFile(const string file_name);

private:
	FileManager() {}
	FileManager(const FileManager&) = delete;

	string buf[1000];
};