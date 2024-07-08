#pragma once
#ifndef interface
#define interface struct
#endif
#include <string>
#include <memory>
#include "command.h"

interface ICommandFactory {
	virtual void injectCommand(const std::string& name, 
		ICommand* command) = 0;
	virtual ICommand* getCommand(const std::string& command) = 0;
};