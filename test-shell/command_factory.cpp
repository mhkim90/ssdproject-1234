#include "command_factory.h"
#include "ReadCommand.h"
#include "WriteCommand.h"
#include "TestApp1Command.h"
#include "TestApp2Command.h"
#include "EraseCommand.h"
#include "EraseRangeCommand.h"
#include "FlushCommand.h"

ICommandFactory& CommandFactory::getInstance()
{
	static CommandFactory instance;
	return instance;
}

void CommandFactory::initialize(ISSD* ssd)
{
	injectCommand("read", new ReadCommand(*ssd));
	injectCommand("write", new WriteCommand(*ssd));
	injectCommand("fullread", new FullReadCommand(*ssd));
	injectCommand("fullwrite", new FullWriteCommand(*ssd));
	injectCommand("testapp1", new TestApp1Command(*ssd));
	injectCommand("testapp2", new TestApp2Command(*ssd));
	injectCommand("erase", new EraseCommand(*ssd));
	injectCommand("erase_range", new EraseRangeCommand(*ssd));
	injectCommand("flush", new FlushCommand(*ssd));
}

void CommandFactory::injectCommand(const std::string& name, ICommand* command)
{
	if (command == nullptr) return;
	commands[name] = command;
}

ICommand* CommandFactory::getCommand(const string& command)
{
	if (commands.count(command) == 1) {
		return commands[command];
	}
	else {
		throw std::invalid_argument("INVALID COMMAND");
	}
}

const std::unordered_map<std::string, ICommand*>& CommandFactory::getAllCommands() const
{
	return commands;
}

CommandFactory::CommandFactory()
{
}
