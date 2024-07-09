#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "SSDManager.cpp"
using namespace std;

int main(int argc, char* argv[])
{
    vector<string> arguments;
    for (int i = 1; i < argc; i++)
    {
        arguments.push_back(argv[i]);
    }

    if (argv[1] == "R" || argv[1] == "r")
    {
        SSDManager ssdManager("read");
        ssdManager.runCommand(stoi(argv[2]));
    }
    else if (argv[1] == "W" || argv[1] == "w")
    {
        SSDManager ssdManager("write");
        ssdManager.runCommand(stoi(argv[2]), argv[3]);
    }
}