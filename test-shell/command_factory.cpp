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

	void injectCommand(const std::string& name, 
			ICommand* command) override {
		commands.insert({ name, command });
	}

	ICommand* getCommand(const string& command) override {
		return commands[command];
	}

private:
	CommandFactory() {
		setCommand();
	}

	void setCommand() {

	}

	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;

	std::unordered_map<std::string, ICommand*> commands;
};