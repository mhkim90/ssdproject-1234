#include "shell.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <fstream>

using namespace std;

Shell::Shell(ICommandFactory& factory)
	: _factory { factory }
{
}

inline string Shell::waitForCommand() {
	static constexpr int BUFFER_LENGTH = 50;
	char rst[BUFFER_LENGTH] = { 0 };
	cin.getline(rst, BUFFER_LENGTH);
	return rst;
}

vector<string> Shell::parsingCommandStr(const string& str)
{
	if (str.empty()) throw invalid_argument("INVALID COMMAND");
	vector<string> rst;
	istringstream stream{ str };
	string buffer;
	while (getline(stream, buffer, ' ')) {
		if (buffer.empty()) continue;
		rst.push_back(buffer);
	}
	return rst;
}

void Shell::run()
{
	while (true) {
		cout << "SHELL > ";
		
		string commandStr = waitForCommand();
		if (commandStr.empty()) continue;

		try {
			vector<string> parsed = parsingCommandStr(commandStr);
			if (parsed.front() == "exit") return;
			if (parsed.front() == "help") {
				help();
				continue;
			}

			vector<string> args{ parsed.begin() + 1, parsed.end() };
			_factory.getCommand(parsed.front())->execute(args);
		}
		catch (invalid_argument& ex) {
			cout << ex.what() << endl;
		}
	}
}

void Shell::runSequence(const string& filePath)
{
	if (filesystem::is_directory(filePath))
		throw invalid_argument("The file path could not be found.");
	if (filesystem::exists(filePath) == false)
		throw invalid_argument("The file path could not be found.");

	loadSequence(filePath);
}

void Shell::help()
{
	cout << "< Help >" << endl;
	for (auto& cmd : _factory.getAllCommands()) {
		cout << cmd.first;

		for (float indent = 0; indent < ((float)8 / cmd.first.length()); ++indent) {
			cout << '\t';
		}

		cout << ": " << cmd.second->getHelp() << endl;
	}
}

void Shell::loadSequence(const string& filePath)
{
	_sequence = {};

	ifstream ifile{ filePath };
	if (ifile.fail()) throw invalid_argument("Faild of file open.");

	stringstream streamBuffer;
	streamBuffer << ifile.rdbuf();

	ifile.close();

	istringstream istream{ streamBuffer.str() };
	string readBuffer;
	while (getline(istream, readBuffer, '\n')) {
		if (readBuffer.empty()) continue;
		_sequence.push_back(readBuffer);
	}
}

const list<string>& Shell::getSequence() const
{
	return _sequence;
}
