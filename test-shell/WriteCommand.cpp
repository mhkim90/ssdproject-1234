#include <string>
#include <stdexcept>
#include <regex>
#include "command.h"

class WriteCommand : public ICommand {
public:
	WriteCommand(ISSD& ssd) : ssd{ ssd } {}

	void injectSSD(ISSD& ssd) override
	{
		this->ssd = ssd;
	}

	void execute(CommandArgs& args) override
	{
		checkAddressValidity(args.addr);
		checkValueValidity(args.value);

		ssd.write(args.addr, args.value);
	}

	const string& getHelp() override
	{
		return WRITE_HELP;
	}

private:
	ISSD& ssd;
	//const string HELP = "write [LBA] [data]";
	const string WRITE_HELP = "\
		LBA에 입력 Value 를 기록한다.\n\
		[Example] write [LBA] [Value]\n\
		[Parameters]\n\
		- LBA: 기록할 영역 주소값 (0~99)\n\
		- Value: 기록할 값\n\
		[Returns] 없음\n";
	const int START_LBA = 0;
	const int END_LBA = 99;
	const int NUM_OF_FIELD = END_LBA - (START_LBA - 1);

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
	
};

class FullwriteCommand : public ICommand {
public:
	FullwriteCommand(ISSD& ssd) : ssd{ ssd } {}

	void injectSSD(ISSD& ssd) override
	{
		this->ssd = ssd;
	}

	void execute(CommandArgs& args) override
	{
		checkValueValidity(args.value);

		for (int addr = 0; addr <= END_LBA; addr++) {
			ssd.write(addr, args.value);
		}
	}

	const string& getHelp() override
	{
		return FULLWRITE_HELP;
	}

private:
	ISSD& ssd;
	const string FULLWRITE_HELP = "\
		LBA 0 번부터 99 번 까지 Write를 수행한다.\n\
		[Example] fullwrite [any] [Value]\n\
		[Parameters]\n\
		- any\n\
		- Value: 기록할 값\n\
		[Returns] 없음\n";
	const int START_LBA = 0;
	const int END_LBA = 99;
	const int NUM_OF_FIELD = END_LBA - (START_LBA - 1);

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
};
