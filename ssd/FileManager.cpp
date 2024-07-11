#include "FileManager.h"

FileManager& FileManager::getInstance()
{
	static FileManager instance;
	return instance;
}

void FileManager::initNand() {
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

void FileManager::openNand()
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

void FileManager::writeNand() {
	ofstream writeFile;
	writeFile.open(NANDFILE);
	if (!writeFile.is_open())
		return;

	for (int i = 0; i < LBA_COUNT; i++) {
		writeFile << buf[i] << endl;
	}
	writeFile.close();
}

void FileManager::writeFile(const string file_name, vector<IoDataStruct> cmdList) {
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "writeFile is called :" + *buf);

	ofstream writeFile;
	writeFile.open(file_name);
	if (!writeFile.is_open())
		return;

	for (auto cmd : cmdList) {
		string tempBuffer = to_string(cmd.opcode) + " " + to_string(cmd.lba) + " " + cmd.data;
		writeFile << tempBuffer << endl;
	}
	writeFile.close();
}

// read from nand and save it to result.txt
void FileManager::readNand(int lba) {
	ofstream resultFile;
	resultFile.open(RESULTFILE);

	if (!resultFile.is_open())
		return;

	resultFile << buf[lba] << endl;

	resultFile.close();
}

bool FileManager::updateResult(string data) {
	ofstream resultFile;
	resultFile.open(RESULTFILE);

	if (!resultFile.is_open())
		return false;

	resultFile << data << endl;

	resultFile.close();

	return true;
}

void FileManager::updateNand(int lba, string data) {
	buf[lba] = data;
}

void FileManager::eraseNand(int lba, string data) {
	int range = stoi(data);
	for (int i = 0; i < range; i++) {
		if (lba + i > MAX_LBA)
			break;
		buf[lba + i] = INIT_DATA;
	}
}

void FileManager::flushNand(vector<IoDataStruct> cmdList) {
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

	clearBuffer();
}

void FileManager::clearBuffer() {
	remove("buffer.txt");
}

void FileManager::loadBuffer(const string file_name, string* buf, int& cmdBackupCount)
{
	// ready to file read
	ifstream readFile(file_name);

	if (!readFile.is_open()) {
		return;
	}

	// save data to buf
	int buf_index = 0;
	string data;
	while (getline(readFile, data, '\n')) {
		buf[buf_index++] = data;
		cmdBackupCount++;
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "saved file contents :" + buf[buf_index - 1]);
	}

	readFile.close();
}

void FileManager::initBuffer(const string file_name) {
	// set file as zero
	ifstream checkFile(file_name);

	if (checkFile.good()) {
		checkFile.close();
		return;
	}
}