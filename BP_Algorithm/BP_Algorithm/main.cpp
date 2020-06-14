#include<iostream>
#include"armadillo"
#include"BPNet.h"

using namespace std;
using namespace arma;

int main()
{
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		double num = (rand() % (2000) / 1000.0 - 1);
		cout << num << endl;
	}

	std::cout << "Hello World £¡" << std::endl;
}
