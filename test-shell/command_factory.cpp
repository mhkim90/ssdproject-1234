#include "command_factory.h"
#include "command.h"
#include <unordered_map>
#include <iostream>
#include <memory>
#include "ReadCommand.h"
#include "WriteCommand.h"
#include "TestApp1Command.h"
#include "TestApp2Command.cpp"
#include "EraseCommand.cpp"
#include "EraseRangeCommand.cpp"

class CommandFactory : public ICommandFactory {
public:
	static CommandFactory& getInstance() {
		static CommandFactory instance;
		return instance;
	}

	void initialize(ISSD* ssd) override {
		injectCommand("read", new ReadCommand(*ssd));
		injectCommand("write", new WriteCommand(*ssd));
		injectCommand("fullread", new FullReadCommand(*ssd));
		injectCommand("fullwrite", new FullWriteCommand(*ssd));
		injectCommand("testapp1", new TestApp1Command(*ssd));
		injectCommand("testapp2", new TestApp2Command(*ssd));
		injectCommand("erase", new EraseCommand(*ssd));
		injectCommand("erase_range", new EraseRangeCommand(*ssd));
	}

	void injectCommand(const std::string& name, 
			ICommand* command) override {
		if (commands.count(name) == 0) {
			commands.insert({ name, command });
		}
	}

	ICommand* getCommand(const string& command) override {
		if (commands.count(command) == 1) {
			return commands[command];
		}
		else {
			throw std::invalid_argument("INVALID COMMAND");
		}
	}

	const std::unordered_map<std::string, ICommand*>& getAllCommands() const override {
		return commands;
	}

private:
	CommandFactory() {}

	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;

	std::unordered_map<std::string, ICommand*> commands;
};