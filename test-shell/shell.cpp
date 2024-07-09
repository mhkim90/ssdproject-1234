#include "shell.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

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
		cout << "Shell > ";
		
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

void Shell::help()
{
	cout << "< Shell Help >" << endl;
	for (auto& cmd : _factory.getAllCommands()) {
		cout << cmd.first << "\t\t: " << cmd.second->getHelp() << endl;
	}
}
