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
		if (commands.count(command) == 1) {
			return commands[command];
		}
		else {
			throw std::invalid_argument("getCommand: cannot find" + command);
		}
	}

	const std::unordered_map<std::string, ICommand*>& getAllCommands() const override {
		return commands;
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