#include <iostream>

int main(int argv, char* argc[])
{
	std::cout << "app launch is done with following inputs : ";
	for (int i = 1; i < argv; i++) {
		std::cout << argc[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}