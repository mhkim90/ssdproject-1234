#include <string>
#include <stdexcept>
#include "command.h"

class EraseRangeCommand : public CommandBase {
public:
	EraseRangeCommand(ISSD& ssd, int argsCount = 2)
		: CommandBase(ssd, argsCount)
	{
	}

	void execute(const vector<string>& args) override
	{
		verifyArgsCount(args);
		verifyFormatAddress(args[0]);
		verifyFormatAddress(args[1]);

		int start_addr = stoi(args[0]);
		int end_addr = stoi(args[1]);

		verifyAddressRange(start_addr);
		if (end_addr > ERASE_END_LBA) {
			end_addr = ERASE_END_LBA;
		}

		if (start_addr >= end_addr) {
			throw std::invalid_argument("wrong range. Check help.");
		}

		while (start_addr < end_addr) {
			int end = start_addr + ERASE_SIZE_AT_ONCE;
			if (end > end_addr) end = end_addr;

			getSSD().erase(start_addr, end - start_addr);

			start_addr += ERASE_SIZE_AT_ONCE;
		}
	}

	const string& getHelp() override {
		return _HELP_MESSAGE;
	}

private:
	const string _HELP_MESSAGE = "Delete a specific range of SSD.\n\
		[Example] erase START_LBA END_LBA\n\
		[Parameters]\n\
		- START_LBA: Start-address to delete(0~99)\n\
		- END_LBA: End-address to delete(1~100)\n\
		[Returns] None\n";

	const int ERASE_SIZE_AT_ONCE = 10;
	const int ERASE_END_LBA = 100;

};
