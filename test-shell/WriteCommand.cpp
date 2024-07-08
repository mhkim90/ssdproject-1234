#include "command.h"

class WriteCommand : public ICommand {
public:
	WriteCommand(ISSD& ssd) : ssd{ ssd } {}

	void injectSSD(ISSD& ssd) override
	{
		this->ssd = ssd;
	}

	void excute(CommandArgs& args) override
	{
		ssd.write(args.addr, args.value);
	}

	const string& getHelp() override
	{
		return HELP;
	}

private:
	ISSD& ssd;
	const string HELP = "write [LBA] [data]";
	
};

class FullwriteCommand : public ICommand {
public:
	FullwriteCommand(ISSD& ssd) : ssd{ ssd } {}

	void injectSSD(ISSD& ssd) override
	{
		this->ssd = ssd;
	}

	void excute(CommandArgs& args) override
	{
		for (int i = 0; i < 100; i++) {
			ssd.write(i, args.value);
		}
	}

	const string& getHelp() override
	{
		return HELP;
	}

private:
	ISSD& ssd;
	const string HELP = "fullwrite [LBA] [data]";

};
