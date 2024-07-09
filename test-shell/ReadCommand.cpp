#include "command.h"
#include "Printer.cpp"
#include <stdexcept>

class ReadCommand : public ICommand {
public:
	ReadCommand(ISSD& ssd) :ssd{ &ssd } {}

	void injectSSD(ISSD& ssd) override
	{
		this->ssd = &ssd;
	}

	void execute(const vector<string>& args) override
	{
		Printer& printer = Printer::getInstance();
		int addr = stoi(args[0]);
		validationCheck(addr);
		printer.print(ssd->read(addr));
	}

	const string& getHelp() override
	{
		return strHelp;
	}

private:
	ISSD* ssd;
	const int LBA_MIN_VAL = 0;
	const int LBA_MAX_VAL = 99;
	const string strHelp = "Reads the value written at LBA and displays it on the screen.\n\
		[Example] read LBA\n\
		[Parameters]\n\
		- LBA: LBA area value to read(0~99)\n\
		[Returns] Displays the data read from LBA.\n";

	void validationCheck(int addr) {
		if (addr < LBA_MIN_VAL || addr > LBA_MAX_VAL) {
			throw std::invalid_argument("INVALID ARGUMENTS");
		}
	}
};

class FullReadCommand : public ICommand {
public:
	FullReadCommand(ISSD& ssd) :ssd{ &ssd } {}
	void injectSSD(ISSD& ssd) override
	{
		this->ssd = &ssd;
	}

	void execute(const vector<string>& args) override
	{
		Printer& printer = Printer::getInstance();
		for (int i = LBA_MIN_VAL; i <= LBA_MAX_VAL; i++) {
			printer.print(ssd->read(i));
		}
	}

	const string& getHelp() override
	{
		return strHelp;
	}

private:
	ISSD* ssd;
	const int LBA_MIN_VAL = 0;
	const int LBA_MAX_VAL = 99;
	const string strHelp = "Reads and displays values from LBA 0 to 99 on the screen.\n\
		[Example] fullread\n\
		[Parameter] None\n\
		[Returns] Displays the data read from each LBA.\n";

};