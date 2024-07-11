#include "ScriptLauncher.h"
#include "json.hpp"
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include "command_factory.h"

using json = nlohmann::json;
using namespace std;

ScriptLauncher::ScriptLauncher(ISSD& ssd, const string& scriptName)
	: ScriptBase(ssd, scriptName)
	, _scriptFilePath { ".\\script\\" + scriptName + ".json" }
{
}

void ScriptLauncher::execute(const vector<string>& args)
{
	printRun();

	try {
		for (auto& invoker : _seq) {
			invoker->run();
		}
	}
	catch (exception& ex) {
		// TODO: logger(ex.what())
		printResult(false);
		throw logic_error{ ex.what() };
	}

	printResult(true);
}

const string& ScriptLauncher::getHelp()
{
	return _help;
}

ScriptLauncher& ScriptLauncher::load()
{
	_seq.clear();

	if (filesystem::exists(_scriptFilePath) == false) {
		throw logic_error("script file path");
	}

	ifstream script{ _scriptFilePath };
	if (!script) {
		throw logic_error("script file open failed");
	}

	json jdata;

	try {
		script >> jdata;

		_help = jdata["help"];
		for (auto& seqNode : jdata["seq"]) {
			auto invoker = Invoker::Builder::newInstance()->cmd(seqNode["cmd"])
				.args(seqNode["args"].get<vector<string>>())
				.tryCnt(seqNode["tryCnt"])
				.verify(seqNode["verify"].is_null() ? nullptr : seqNode["verify"].get<string>().c_str())
				.build();

			_seq.push_back(invoker);
		}
	}
	catch (exception& ex) {
		throw logic_error{ ex.what() };
	}
	catch (...) {
		throw logic_error("script json data load failed.");
	}

	return *this;
}

ScriptLauncher::Invoker::Builder::Builder()
	: _tryCnt{ 0 }
{
}

shared_ptr<ScriptLauncher::Invoker::Builder> ScriptLauncher::Invoker::Builder::newInstance()
{
	return shared_ptr<Builder>{new Builder()};
}

ScriptLauncher::Invoker::Builder& ScriptLauncher::Invoker::Builder::cmd(const string& value)
{
	_cmd = value;
	return *this;
}

ScriptLauncher::Invoker::Builder& ScriptLauncher::Invoker::Builder::args(const vector<string>& value)
{
	_args = value;
	return *this;
}

ScriptLauncher::Invoker::Builder& ScriptLauncher::Invoker::Builder::tryCnt(unsigned int value)
{
	_tryCnt = value;
	return *this;
}

ScriptLauncher::Invoker::Builder& ScriptLauncher::Invoker::Builder::verify(const char* value)
{
	if (nullptr == value) return *this;
	_verify = shared_ptr<string>{ new string {value} };
	return *this;
}

shared_ptr<ScriptLauncher::Invoker> ScriptLauncher::Invoker::Builder::build()
{
	shared_ptr<Invoker> rst{ new Invoker() };
	rst->_cmd = _cmd;
	rst->_args = _args;
	rst->_tryCnt = _tryCnt;
	rst->_verify = _verify;
	return rst;
}

void ScriptLauncher::Invoker::run()
{
	auto& factory = CommandFactory::getInstance();

	beginStreamCapture();
	for (unsigned int cnt = 0; cnt < _tryCnt; ++cnt) {
		ICommand* command = factory.getCommand(_cmd);
		command->execute(_args);
	}
	endStreamCapture();

	verify();
}

ScriptLauncher::Invoker::Invoker()
	: _tryCnt{ 0 }
	, _befoBuffer {nullptr}
{
}

void ScriptLauncher::Invoker::beginStreamCapture()
{
	_befoBuffer = cout.rdbuf();
	cout.set_rdbuf(_osstream.rdbuf());
}

void ScriptLauncher::Invoker::endStreamCapture()
{
	cout.set_rdbuf(_befoBuffer);
}

void ScriptLauncher::Invoker::verify()
{
	if (_verify == nullptr) return;
	if ((*_verify) == _osstream.str()) return;

	throw logic_error(
		"verify failed!\n---check value---\n"
		+ (*_verify)
		+ "\n---logic value---\n"
		+ _osstream.str()
	);
}
