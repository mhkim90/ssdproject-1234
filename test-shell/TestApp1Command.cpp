#include "command.h"
#include <stdexcept>

class TestApp1 : public ICommand {
public:
	TestApp1(ISSD& ssd, ICommand& read, ICommand& write)
		: ssd{ &ssd }, read{ &read }, write{ &write } {}
	void injectSSD(ISSD& ssd) override
	{

	}

	void execute(const vector<string>& args) override
	{
		write->execute(args);
		read->execute(args);
	}

	const string& getHelp() override
	{
		return strHelp;
	}

private:
	ISSD* ssd;
	ICommand *read, *write;
	const int LBA_MIN_VAL = 0;
	const int LBA_MAX_VAL = 99;
	const string TEST_VAL = "0xAAAABBBB";
	const string strHelp = "";

};