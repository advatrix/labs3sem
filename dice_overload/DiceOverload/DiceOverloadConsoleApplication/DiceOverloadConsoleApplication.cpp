#include <iostream>
#include "DiceOverloadLib.h"
#include "labslib.h"
#include "App.h"

using namespace labslib;

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
