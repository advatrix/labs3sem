#include "dice_dynamic_lib.h"
#include <iostream>

#include "labslib.h"
#include "app_ns.h"

using namespace labslib;
using namespace app;


int main() {
	DiceDyn::Dice dice;
	std::cout << dice;
	int d = 0;
	do {
		d = dialog();
		menu(d, dice);
	} while (d);
	return 0;
}