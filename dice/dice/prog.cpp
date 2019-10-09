#include "prog.h"
namespace prog {
	int dialog() {
		print("choose what to do");
		print("0 - quit");
		print("1 - print dice");
		print("2 - roll");
		print("3 - add new dice");
		print("4 - remove a dice");
		print("5 - remove all dice");
		print("6 - get a dice points");
		print("7 - get group points");
		print("8 - check coincidences");
		int d = 0;
		input(d);
		return d;
	}

	void menu(int d, dicens::Dice& dice) {
		switch (d) {
		case 0: return;
		case 1: {
			dice.print(std::cout);
			break;
		}
		case 2: {
			dice.roll();
			dice.print(std::cout);
			break;
		}
		case 3: {
			int pts;
			print("enter points");
			input(pts);
			try {
				dice.add(pts);
				dice.print(std::cout);
			}
			catch (std::exception& e) {
				print(e.what());
			}
			break;
		}
		case 4: {
			int n;
			print("enter n");
			input(n);
			try {
				dice.remove(n);
				dice.print(std::cout);
			}
			catch (std::exception& e) {
				print(e.what());
			}
			break;
		}
		case 5: {
			dice.remove();
			dice.print(std::cout);
			break;
		}
		case 6: {
			int n;
			print("input n");
			input(n);
			try {
				print(dice.getPts(n));
			}
			catch (std::exception& e) {
				print(e.what());
			}
			break;
		}
		case 7: {
			print(dice.sum());
			break;
		}
		case 8: {
			bool t = dice.coincidence();
			if (t) print("found");
			else print("not found");
			break;
		}
		default: {
			print("incorrect choice");
		}
		}
	}
}
