#include <string>
#include <stdexcept>
#include <regex>
#include "command.h"

class WriteCommand : public ICommand {
public:
	const int START_LBA = 0;
	const int END_LBA = 99;

	WriteCommand(ISSD& ssd) : ssd{ ssd } {}

	void injectSSD(ISSD& ssd) override
	{
		this->ssd = ssd;
	}

	void execute(const vector<string>& args) override
	{
		int addr = stoi(args[0]);
		std::string value = args[1];

		checkAddressValidity(addr);
		checkValueValidity(value);

		ssd.write(addr, value);
	}

	const string& getHelp() override
	{
		return WRITE_HELP;
	}

	void checkAddressValidity(int addr) {
		if (addr < START_LBA || addr > END_LBA) {
			throw std::invalid_argument("addr is out of range");
		}
	}

	void checkValueValidity(string value) {
		std::regex reg("0x[0-9A-F]{8}$");
		if (!regex_match(value, reg))
			throw std::invalid_argument("value is not in A~F, 0~9");
	}

	ISSD& getSsd() {
		return ssd;
	}

private:
	ISSD& ssd;
	const string WRITE_HELP = "\
		LBA에 입력 Value 를 기록한다.\n\
		[Example] write [LBA] [Value]\n\
		[Parameters]\n\
		- LBA: 기록할 영역 주소값 (0~99)\n\
		- Value: 기록할 값\n\
		[Returns] 없음\n";
	
};

class FullwriteCommand : public WriteCommand {
public:
	FullwriteCommand(ISSD& ssd) : WriteCommand{ ssd } {}

	void injectSSD(ISSD& ssd) override
	{
		WriteCommand::injectSSD(ssd);
	}

	void execute(const vector<string>& args) override
	{
		std::string value = args[0];

		checkValueValidity(value);

		writeAtAllSsdField(value);
	}

	void writeAtAllSsdField(std::string& value)
	{
		for (int addr = START_LBA; addr <= END_LBA; addr++) {
			getSsd().write(addr, value);
		}
	}

	const string& getHelp() override
	{
		return FULLWRITE_HELP;
	}

private:
	const string FULLWRITE_HELP = "\
		LBA 0 번부터 99 번 까지 Write를 수행한다.\n\
		[Example] fullwrite [any] [Value]\n\
		[Parameters]\n\
		- any\n\
		- Value: 기록할 값\n\
		[Returns] 없음\n";
};
