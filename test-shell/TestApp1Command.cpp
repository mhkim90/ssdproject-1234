#include "command.h"
#include "Printer.cpp"

class TestApp1Command : public CommandBase {
public:
	TestApp1Command(ISSD& ssd, ICommand& read, ICommand& write)
		: CommandBase(ssd)
		, _read{ read }
		, _write{ write } {

	}

	void execute(const vector<string>& args) override
	{
		Printer& printer = Printer::getInstance();

		_write.execute({ TEST_VAL });
		for (int i = _ADDR_RANGE_MIN; i <= _ADDR_RANGE_MAX; i++) {
			string tmp = getSSD().read(i);
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
	ICommand &_read, &_write;
	const string TEST_VAL = "0xAAAABBBB";
	const string strHelp = "Test script1 - testapp1.\n\
		[Example] testapp1\n\
		[Parameters]\n\
		- None \n\
		[Returns] Display Pass or Fail\n";

};