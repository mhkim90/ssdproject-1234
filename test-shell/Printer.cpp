#pragma once
#include <iostream>

using namespace std;

class Printer {
public:
	static Printer& getInstance() {
		static Printer instance;
		return instance;
	}

	void print(string str) {
		cout << str << "\n";
	}

private:
	Printer() { }
};