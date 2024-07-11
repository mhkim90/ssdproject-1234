#pragma once
#include "command.h"
#include <list>
#include <memory>
#include <iostream>
#include <sstream>

using std::list;
using std::shared_ptr;
using std::ostringstream;
using std::streambuf;

class ScriptLauncher : public ScriptBase {
public:
	ScriptLauncher(ISSD& ssd, const string& scriptName);
	virtual void execute(const vector<string>& args) override;
	virtual const string& getHelp() override;

	ScriptLauncher& load();

private:
	class Invoker {
	public:
		void run();

		class Builder {
		public:
			static shared_ptr<Builder> newInstance();
			Builder& cmd(const string& value);
			Builder& args(const vector<string>& value);
			Builder& tryCnt(unsigned int value);
			Builder& verify(const vector<string>& value);
			shared_ptr<Invoker> build();

		private:
			Builder();

			string _cmd;
			vector<string> _args;
			unsigned int _tryCnt;
			shared_ptr<vector<string>> _verify;
		};

	private:
		Invoker();
		void beginStreamCapture();
		void endStreamCapture();
		void verify();

		string _cmd;
		vector<string> _args;
		unsigned int _tryCnt;
		shared_ptr<vector<string>> _verify;

		ostringstream _osstream;
		streambuf* _befoBuffer;
	};

	const string _scriptFilePath;
	string _help;
	list<shared_ptr<Invoker>> _seq;
};