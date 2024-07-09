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
	if (str.empty()) throw invalid_argument("input string empty");
	vector<string> rst;
	istringstream stream{ str };
	string buffer;
	while (getline(stream, buffer, ' ')) {
		if (buffer.empty()) continue;
		rst.push_back(buffer);
	}
	return rst;
}
