#pragma once
#include <fstream>
#include <iostream>
#include <stdio.h>
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

	void clearBuffer();

	void loadBuffer(const string file_name, string* buf, int& cmdBackupCount);

	void initBuffer(const string file_name);

protected:
	ILogger& logger = Logger::getInstance("ssd");

private:
	FileManager() {}
	FileManager(const FileManager&) = delete;

	string buf[LBA_COUNT];
};