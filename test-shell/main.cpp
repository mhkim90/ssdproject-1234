#include "ssdlib.cpp"
#include "shell.h"
#include "command_factory.cpp"
#include "ReadCommand.cpp"
#include "WriteCommand.cpp"
#include "TestApp1Command.cpp"
#include "TestApp2Command.cpp"

int main() {
	ICommandFactory& factory = CommandFactory::getInstance();
	std::string path = "\\..\\x64\\Debug";
	std::string app_name = "\\ssd.exe";
	std::string result_path = "";
	ISSD* ssd = new SSDLib(path, app_name, result_path);

	ICommand* fullReadCMD = new FullReadCommand(*ssd);
	ICommand* fullWriteCMD = new FullWriteCommand(*ssd);

	factory.injectCommand("read", new ReadCommand(*ssd));
	factory.injectCommand("write", new WriteCommand(*ssd));
	factory.injectCommand("fullread", new FullReadCommand(*ssd));
	factory.injectCommand("fullwrite", new FullWriteCommand(*ssd));
	factory.injectCommand("testapp1", new TestApp1(*ssd,
		*fullReadCMD, *fullWriteCMD));
	factory.injectCommand("testapp2", new TestApp2Command(*ssd));

	Shell* shell = new Shell(factory);
	shell->run();
}