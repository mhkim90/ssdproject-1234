#pragma once
#include <stdexcept>
using namespace std;

class InvalidOpcodeException : public exception
{
public:
	char const* what() const override
	{
		return "invalid opcode !! check code";
	}
};

class LbaRangeOverException : public exception
{
public:
	char const* what() const override
	{
		return "lba is invalid !!";
	}
};
