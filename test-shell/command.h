#pragma once
#ifndef interface
#define interface struct
#endif

#include <vector>
#include <string>
#include "ssd.h"
using std::string;
using std::vector;


interface ICommand {
	virtual void injectSSD(ISSD& ssd) = 0;
	virtual void execute(const vector<string>& args) = 0;
	virtual const string& getHelp() = 0;
};

class CommandBase : public ICommand {
public:
	CommandBase(ISSD& ssd, const string&  helpMsg, int verifyArgsCount = 0);

	virtual void execute(const vector<string>& args) = 0;

	virtual void injectSSD(ISSD& ssd) override;
	virtual const string& getHelp() override;

protected:
	inline void verifyArgsCount(const vector<string>& args) const;
	inline void verifyFormatAddress(const string& arg) const;
	inline void verifyFormatValue(const string& arg) const;
	inline void verifyAddressRange(int addr) const;
	inline ISSD& getSSD() const;

private:
	static constexpr int ADDR_RANGE_MIN = 0;
	static constexpr int ADDR_RANGE_MAX = 99;

	ISSD& _ssd;
	const int _VERIFY_ARGS_COUNT;
	const string _HELP_MSG;
};