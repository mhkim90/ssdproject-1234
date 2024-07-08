#include <stdio.h>

class CmdHandler
{
public:
	virtual void fileOpen() = 0;
	virtual void fileClose() = 0;
	virtual void execute(int lba, int data = 0) = 0;
private:

};