#include "command.h"
#include <stdexcept>
#include <iostream>

class ReadCommand : public ICommand {
public:
	ReadCommand(ISSD& ssd) :ssd{ &ssd } {}

	void injectSSD(ISSD& ssd) override
	{
		this->ssd = &ssd;
	}

	void execute(const vector<string>& args) override
	{
		int addr = stoi(args[0]);
		validationCheck(addr);
		ssd->read(addr);
	}

	const string& getHelp() override
	{
		return strHelp;
	}

private:
	ISSD* ssd;
	const int LBA_MIN_VAL = 0;
	const int LBA_MAX_VAL = 99;
	const string strHelp = "\
		LBA에 적힌 값을 읽어 화면에 출력한다.\n \
		[Example] read LBA\n \
		[Parameters]\n \
		- LBA: 값을 읽을 LBA 영역 값 (0~99)\n \
		[Returns] LBA에서 읽은 데이터를 출력합니다.\n";

	void validationCheck(int addr) {
		if (addr < LBA_MIN_VAL || addr > LBA_MAX_VAL) {
			throw std::invalid_argument("잘못된 LBA 값 입니다.");
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
		for (int i = LBA_MIN_VAL; i <= LBA_MAX_VAL; i++) {
			ssd->read(i);
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
	const string strHelp = "\
		LBA 0 번부터 99 번 까지 값을 읽어 화면에 출력한다.\n \
		[Example] fullread\n \
		[Returns] 각 LBA에서 읽은 데이터를 출력합니다.\n";

};