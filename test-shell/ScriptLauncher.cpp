#include "ScriptLauncher.h"
#include "json.hpp"

using json = nlohmann::json;

ScriptLauncher::ScriptLauncher(ISSD& ssd, const string& scriptName)
	: ScriptBase(ssd, scriptName)
{
}

void ScriptLauncher::execute(const vector<string>& args)
{
}

const string& ScriptLauncher::getHelp()
{
	return _help;
}

void ScriptLauncher::loadScript()
{

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
}

ScriptLauncher::Invoker::Invoker()
	: _tryCnt{ 0 }
	, _befoBuffer {nullptr}
{
}

void ScriptLauncher::Invoker::beginStreamCapture()
{
}

void ScriptLauncher::Invoker::endStreamCapture()
{
}

bool ScriptLauncher::Invoker::verify()
{
	return false;
}
