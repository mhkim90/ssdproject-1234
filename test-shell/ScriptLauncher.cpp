#include "ScriptLauncher.h"
#include "json.hpp"
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <numeric>
#include <functional>
#include "command_factory.h"

using json = nlohmann::json;
using namespace std;

ScriptLauncher::ScriptLauncher(ISSD& ssd, const string& scriptName)
	: ScriptBase(ssd, scriptName)
	, _scriptFilePath { ".\\" + scriptName + ".json" }
{
}

void ScriptLauncher::execute(const vector<string>& args)
{
	printRun();

	try {
		for (auto& invoker : _seq) {
			invoker->invoke();
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

ScriptLauncher& ScriptLauncher::compile()
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
			Args args{};
			args.address.begin = seqNode["args"]["address"]["begin"];
			args.address.end = seqNode["args"]["address"]["end"];

			const auto& valueNode = seqNode["args"]["value"];
			if (valueNode.is_null() == false) args.value = valueNode;

			auto invoker = Invoker::Builder::newInstance()->cmd(seqNode["cmd"])
				.args(args)
				.tryCnt(seqNode["tryCnt"])
				.verify(seqNode["verify"].get<vector<string>>())
				.build();

			_seq.push_back(invoker);
		}
	}
	catch (exception&) {
		throw logic_error("script json data compile failed.");
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

ScriptLauncher::Invoker::Builder& ScriptLauncher::Invoker::Builder::args(const Args& value)
{
	_args = value;
	return *this;
}

ScriptLauncher::Invoker::Builder& ScriptLauncher::Invoker::Builder::tryCnt(unsigned int value)
{
	_tryCnt = value;
	return *this;
}

ScriptLauncher::Invoker::Builder& ScriptLauncher::Invoker::Builder::verify(const vector<string>& value)
{
	_verify = shared_ptr<vector<string>>{ new vector<string> {value} };
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

void ScriptLauncher::Invoker::invoke()
{
	auto& factory = CommandFactory::getInstance();

	beginStreamCapture();
	for (unsigned int cnt = 0; cnt < _tryCnt; ++cnt) {
		ICommand* command = factory.getCommand(_cmd);
		for (unsigned int addr = _args.address.begin; addr <= _args.address.end; ++addr) {
			vector<string> args{ to_string(addr) };
			if (_args.value.empty() == false) args.push_back(_args.value);
			command->execute(args);
		}
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
	if (_verify->empty()) return;

	vector<string> actual;
	istringstream isstream{ _osstream.str() };
	string buffer;
	while (getline(isstream, buffer, '\n')) {
		if (buffer.empty()) continue;
		actual.push_back(buffer);
	}

	if ((*_verify) == actual) return;

	auto joindVerify = accumulate(next(_verify->begin()), _verify->end(),
		(*_verify)[0],
		[](const string& a, const string& b) { return a + ',' + b; });
	auto joindActual = accumulate(next(actual.begin()), actual.end(),
		actual[0],
		[](const string& a, const string& b) { return a + ',' + b; });

	throw logic_error(
		"verify failed!\n---check value---\n"
		+ joindVerify
		+ "\n---logic value---\n"
		+ joindActual
	);
}
