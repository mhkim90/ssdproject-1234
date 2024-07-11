#include "shell.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <fstream>

using namespace std;

Shell::Shell(ICommandFactory& factory)
	: _factory { factory }
	, logger{ Logger::getInstance("shell") }
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
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start Run()");
	while (true) {
		cout << "SHELL > ";
		
		string commandStr = waitForCommand();
		if (commandStr.empty()) continue;

		try {
			vector<string> parsed = parsingCommandStr(commandStr);
			if (parsed.front() == "exit") {
				logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Quit Program");
				return;
			}
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
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End Run()");
}

void Shell::runSequence(const string& filePath)
{
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start RunSequence()");
	try {
		loadSequence(filePath);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
		return;
	}

	while (_sequence.size() > 0) {
		try {
			_factory.getCommand(_sequence.front())->execute({});
		}
		catch (invalid_argument& ex) {
			cout << ex.what() << endl;
		}
		catch (logic_error&) {
			return;
		}
		catch (exception& ex) {
			cout << "Unknown Error : " << ex.what() << endl;
		}
		_sequence.pop_front();
	}
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End RunSequence()");
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
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Start LoadSequence()");
	_sequence = {};

	verifySequenceFilePath(filePath);

	ifstream ifile{ filePath };
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Exception: Invalid Argument");
	if (ifile.fail()) throw invalid_argument("Failed of file open.");

	stringstream streamBuffer;
	streamBuffer << ifile.rdbuf();

	ifile.close();

	istringstream istream{ streamBuffer.str() };
	string readBuffer;
	while (getline(istream, readBuffer, '\n')) {
		if (readBuffer.empty()) continue;
		_sequence.push_back(readBuffer);
	}
	logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "End LoadSequence()");
}

const list<string>& Shell::getSequence() const
{
	return _sequence;
}

void Shell::verifySequenceFilePath(const string& filePath) const
{
	if (filesystem::is_directory(filePath))
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Exception: Invalid Argument");
		throw invalid_argument("The file path could not be found.");
	if (filesystem::exists(filePath) == false)
		logger.printLog(PRINT_TYPE::FILE, __FUNCTION__, "Exception: Invalid Argument");
		throw invalid_argument("The file path could not be found.");
}
