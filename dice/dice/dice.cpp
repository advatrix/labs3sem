

#include <iostream>
#include "DiceLib.h"
#include "prog.h"

using namespace dicens;
using namespace prog;

int main()
{
	Dice dice;
	int q = 0;
	dice.print(std::cout);
	do {
		int d = dialog();
		menu(d, dice);
		print("continue? 0/1");
		input(q);
	} while (q);
	return 0;
	
}
