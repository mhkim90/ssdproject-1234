#include "shell.h"
#include <iostream>

using std::cin;

Shell::Shell(ICommandFactory& factory)
	: _factory { factory }
{
}

inline string Shell::waitForCommand() {
	char rst[50] = { 0 };
	cin.getline(rst, 50);
	return rst;
}
