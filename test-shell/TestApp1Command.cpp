#include "command.h"
#include "Printer.cpp"

class TestApp1 : public ICommand {
public:
	TestApp1(ISSD& ssd, ICommand& read, ICommand& write)
		: ssd{ &ssd }, read{ &read }, write{ &write } {}
	void injectSSD(ISSD& ssd) override
	{
		this->ssd = &ssd;
	}

	void execute(const vector<string>& args) override
	{
		Printer& printer = Printer::getInstance();

		write->execute({ TEST_VAL });
		for (int i = LBA_MIN_VAL; i <= LBA_MAX_VAL; i++) {
			string tmp = ssd->read(i);
			if (tmp != TEST_VAL) {
				printer.print("FAIL");
				return;
			}
		}
		printer.print("SUCCESS");
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