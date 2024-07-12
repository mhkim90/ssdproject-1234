#pragma once
#ifndef interface
#define interface struct
#endif

#include <vector>
#include <list>
#include "command.h"
#include "command_factory.h"

using std::vector;
using std::list;

class Shell {
public:
	Shell(ICommandFactory& factory);
	
	void run();
	void runSequence(const string& filePath);

	virtual string waitForCommand();
	vector<string> parsingCommandStr(const string& str);
	void help();
	void loadSequence(const string& filePath);
	const list<string>& getSequence() const;
	unsigned int loadScripts(ISSD& ssd);

protected:
	void verifySequenceFilePath(const string& filePath) const;
	ILogger& logger;

private:

	ICommandFactory& _factory;
	list<string> _sequence;
};