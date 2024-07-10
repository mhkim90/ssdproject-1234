#include "command.h"
#include "Printer.cpp"
#include <stdexcept>

class ReadCommand : public CommandBase {
public:
	ReadCommand(ISSD& ssd)
		: CommandBase(ssd, 1)
	{
	}

	void execute(const vector<string>& args) override
	{
		verifyArgsCount(args);
		verifyFormatAddress(args[0]);
		Printer& printer = Printer::getInstance();
		int addr = stoi(args[0]);
		verifyAddressRange(addr);
		printer.print(getSSD().read(addr));
	}

	const string& getHelp() override {
		return _HELP_MESSAGE;
	}

private:
	const string _HELP_MESSAGE = "Reads the value written at LBA and displays it on the screen.\n\
		[Example] read [LBA]\n\
		[Parameters]\n\
		- LBA: LBA area value to read(0~99)\n\
		[Returns] Displays the data read from LBA.\n";
};

class FullReadCommand : public CommandBase {
public:
	FullReadCommand(ISSD& ssd)
		: CommandBase(ssd) {

	}

	void execute(const vector<string>& args) override
	{
		Printer& printer = Printer::getInstance();
		for (int i = _ADDR_RANGE_MIN; i <= _ADDR_RANGE_MAX; i++) {
			printer.print(getSSD().read(i));
		}
	}

	const string& getHelp() override
	{
		return strHelp;
	}

private:
	const string strHelp = "Reads and displays values from LBA 0 to 99 on the screen.\n\
		[Example] fullread\n\
		[Parameter] None\n\
		[Returns] Displays the data read from each LBA.\n";

};