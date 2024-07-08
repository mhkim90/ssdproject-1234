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
	const string strHelp = "TEST";
};