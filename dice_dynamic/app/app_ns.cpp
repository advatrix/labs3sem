#include "app_ns.h"
using namespace labslib;
namespace app {

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
		print("9 - add new group of dice");
		int d = 0;
		input(d);
		return d;
	}

	void menu(int d, DiceDyn::Dice& dice) {
		switch (d) {
		case 0: return;
		case 1: {
			std::cout << dice;
			break;
		}
		case 2: {
			dice.roll();
			std::cout << dice;
			break;
		}
		case 3: {
			int pts;
			print("enter points");
			input(pts);
			try {
				dice += pts;
				std::cout << dice;
			}
			catch (std::exception& e) {
				print(e.what());
			}
			break;
		}
		case 4: {
			int n;
			print("enter number of pts to remove");
			input(n);
			try {
				dice -= n;
				std::cout << dice;
			}
			catch (std::exception& e) {
				print(e.what());
			}
			break;
		}
		case 5: {
			dice.remove();
			std::cout << dice;
			break;
		}
		case 6: {
			int n;
			print("input n");
			input(n);
			try {
				int points = dice[n - 1];
				print(points);
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
		case 9: {
			print("enter number of dice in a group");
			int n, setCond;
			input(n);
			print("do you want to set points? 0/1");
			input(setCond);
			if (setCond) {
				int* tmp = new int[n];
				for (int i = 0; i < n; i++) {
					std::cout << "enter points for dice " << i + 1 << " ";
					input(tmp[i]);

				}
				try {
					DiceDyn::Dice newdice(n, tmp);
					std::cout << newdice;
					dice = dice + newdice;
				}
				catch (std::exception& e) {
					print(e.what());
					break;
				}
				delete[] tmp;
			}
			else {
				try {
					DiceDyn::Dice newdice(n);
					std::cout << newdice;
					dice = dice + newdice;
				}
				catch (std::exception& e) {
					print(e.what());
					break;
				}
			}
			print("merged");
			std::cout << dice;
			break;
		}
		default: {
			print("incorrect choice");
		}
		}
	}

}