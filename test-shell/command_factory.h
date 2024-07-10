#pragma once
#ifndef interface
#define interface struct
#endif
#include <string>
#include <memory>
#include <unordered_map>
#include "command.h"

interface ICommandFactory {
	virtual void injectCommand(const std::string& name, 
		ICommand* command) = 0;
	virtual ICommand* getCommand(const std::string& command) = 0;
	virtual const std::unordered_map<std::string, ICommand*>&
		getAllCommands() const = 0;
	virtual void initialize(ISSD* ssd) = 0;
};