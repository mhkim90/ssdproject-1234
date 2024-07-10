#include <string>
#include <stdexcept>
#include <regex>
#include "command.h"

class WriteCommand : public CommandBase {
public:
	WriteCommand(ISSD& ssd, int argsCount = 2)
		: CommandBase(ssd, argsCount) {

	}

	void execute(const vector<string>& args) override
	{
		verifyArgsCount(args);
		verifyFormatAddress(args[0]);
		verifyFormatValue(args[1]);

		int addr = stoi(args[0]);
		const std::string& value = args[1];

		verifyAddressRange(addr);

		getSSD().write(addr, value);
	}

	const string& getHelp() override
	{
		return WRITE_HELP;
	}

private:
	const string WRITE_HELP = "write Value at LBA address\n\
		[Example] write [LBA] [Value]\n\
		[Parameters]\n\
		- LBA: address (0~99)\n\
		- Value: a value to be recorded\n\
		[Returns] none\n";
	
};

class FullWriteCommand : public WriteCommand {
public:
	FullWriteCommand(ISSD& ssd) : WriteCommand{ ssd, 1 } {}

	void injectSSD(ISSD& ssd) override
	{
		WriteCommand::injectSSD(ssd);
	}

	void execute(const vector<string>& args) override
	{
		verifyArgsCount(args);

		const std::string& value = args[0];
		verifyFormatValue(value);

		writeAtAllSsdField(value);
	}

	void writeAtAllSsdField(const std::string& value)
	{
		for (int addr = _ADDR_RANGE_MIN; addr <= _ADDR_RANGE_MAX; addr++) {
			getSSD().write(addr, value);
		}
	}

	const string& getHelp() override
	{
		return FULLWRITE_HELP;
	}

private:
	const string FULLWRITE_HELP = "Perform write from address 0 to 99.\n\
		[Example] fullwrite [any] [Value]\n\
		[Parameters]\n\
		- any\n\
		- Value: a value to be recorded\n\
		[Returns] none\n";
};
