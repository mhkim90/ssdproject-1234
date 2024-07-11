#include "SSDManager.h"

void SSDManager::runCommand(int lba, string data)
{
	if (true == cmdHandler->sanityCheckPassed(lba, data))
	{
		cmdHandler->execute(lba, data);
	}
	else
	{
		throw LbaRangeOverException();
	}
}