#pragma once
#ifndef interface
#define interface struct
#endif

#include <string>
using std::string;

interface ISSD {
	virtual void write(int addr, const string& value) = 0;
	virtual string read(int addr) = 0;
};