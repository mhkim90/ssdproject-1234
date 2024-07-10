#include "shell.h"
#include "command_factory.cpp"
#include "ssdlib.cpp"

int main() {
	ICommandFactory& factory = CommandFactory::getInstance();
	ISSD* ssd = new SSDLib();
	factory.initialize(ssd);

	Shell* shell = new Shell(factory);
	shell->run();
}