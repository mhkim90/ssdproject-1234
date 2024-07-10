#pragma once

#ifndef interface
#define interface struct
#endif

#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "command.h"

interface ICommandFactory {
	virtual void injectCommand(const std::string& name, 
		ICommand* command) = 0;
	virtual ICommand* getCommand(const std::string& command) = 0;
	virtual const std::unordered_map<std::string, ICommand*>&
		getAllCommands() const = 0;
	virtual void initialize(ISSD* ssd) = 0;
};


class CommandFactory : public ICommandFactory {
public:
	static ICommandFactory& getInstance();

	void initialize(ISSD* ssd) override;

	void injectCommand(const std::string& name,
		ICommand* command) override;

	ICommand* getCommand(const string& command) override;

	const std::unordered_map<std::string, ICommand*>& getAllCommands() const override;

private:
	CommandFactory();

	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;

	std::unordered_map<std::string, ICommand*> commands;
};