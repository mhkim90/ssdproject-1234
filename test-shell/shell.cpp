#include "shell.h"
#include <iostream>

using std::cin;

Shell::Shell(ICommandFactory& factory)
	: _factory { factory }
{
}

inline string Shell::waitForCommand() {
	string inputBuffer;
	cin >> inputBuffer;
	return inputBuffer;
}
