#include "DiceOverloadLib.h"
#include <iostream>

#include "labslib.h"
#include "app_ns.h"

using namespace labslib;
using namespace app;


int main() {
	DiceOL::Dice dice;
	int q = 0;
	std::cout << dice;
	do {
		int d = dialog();
		menu(d, dice);
		print("continue? 0/1");
		input(q);
	} while (q);
	return 0;
}
