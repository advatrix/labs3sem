#include "game.h"

using namespace game;

int main() {
	int p = 0, q;
	do {
		p = dialog();
		menu(p);
		labslib::print("continue? 0/1");
		labslib::input(q);
	} while (q);
	return 0;
}