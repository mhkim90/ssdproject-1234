#pragma once
#ifndef interface
#define interface struct
#endif

#include "command.h"
#include "commnad_factory.h"

interface IShell {

};

class Shell : public IShell {
public:
	Shell(ICommandFactory& factory);
	virtual string waitForCommand();
private:
	ICommandFactory& _factory;
};