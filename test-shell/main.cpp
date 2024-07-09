#include "shell.h"
#include "command_factory.cpp"
#include "ReadCommand.cpp"
#include "WriteCommand.cpp"
#include "ssdlib.cpp"

int main() {
	ICommandFactory& factory = CommandFactory::getInstance();
	std::string path = "\\..\\x64\\Debug";
	std::string app_name = "\\ssd.exe";
	std::string result_path = "";
	ISSD* ssd = new SSDLib(path, app_name, result_path);
	factory.injectCommand("read", new ReadCommand(*ssd));
	factory.injectCommand("write", new WriteCommand(*ssd));
	factory.injectCommand("fullread", new FullReadCommand(*ssd));
	factory.injectCommand("fullwrite", new FullwriteCommand(*ssd));

	Shell* shell = new Shell(factory);
	shell->run();
}