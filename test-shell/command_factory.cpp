#include "command_factory.h"
#include "command.h"
#include <unordered_map>
#include <iostream>
#include <memory>

class CommandFactory : public ICommandFactory {
public:
	static CommandFactory& getInstance() {
		static CommandFactory instance;
		return instance;
	}

	CommandFactory() {
		setCommand();
	}

	void injectCommand(const std::string& name, 
			ICommand* command) override {
		commands.insert({ name, command });
	}

	ICommand* getCommand(const string& command) override {
		return commands[command];
	}

private:
	void setCommand() {

	}

	std::unordered_map<std::string, ICommand*> commands;
};