#include "shell.h"
#include <iostream>

using std::cin;

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
