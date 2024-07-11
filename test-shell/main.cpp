#include "ssdlib.h"
#include "shell.h"
#include "command_factory.h"

int main(int argc, char* argv[]) {
	ICommandFactory& factory = CommandFactory::getInstance();
	ISSD& ssd = SSDLib::getInstance();
	factory.initialize(&ssd);

	Shell* shell = new Shell(factory);

	if (argc > 1) {
		shell->runSequence(argv[1]);
		return 0;
	}

	shell->run();
	
	return 0;
}	