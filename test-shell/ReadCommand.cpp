#include "command.h"

class ReadCommand : public ICommand {
public:
	ReadCommand(ISSD& ssd) :ssd{ &ssd } {}

	void injectSSD(ISSD& ssd) override
	{

	}

	void excute(CommandArgs& args) override
	{
		args.value = ssd->read(args.addr);
	}

	const string& getHelp() override
	{
		return strHelp;
	}

private:
	ISSD* ssd;
	const string strHelp = "\
		LBA에 적힌 값을 읽어 화면에 출력한다.\n \
		[Example] read LBA\n \
		[Parameters]\n \
		- LBA: 값을 읽을 LBA 영역 값 (0~99)\n \
		[Returns] LBA에서 읽은 데이터를 출력합니다.\n";
};