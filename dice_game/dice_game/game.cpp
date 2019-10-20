#include "game.h"
#include "labslib.h"

using namespace labslib;

namespace game {


	int dialog() {
		int ans;
		const char* games[] = { "0. Quit", "1. Classic", "2. Pig", "3. Chicago", "4. Four dice" };
		do {
			for (int i = 0; i < 5; i++) print(games[i]);
			std::cout << "Make your choice: --> ";
			input(ans);
			if (ans >= 0 && ans < 5) continue;
			print("You've made an incorrect choice, try again");
		} while (ans < 0 || ans > 4);
		return ans;
	}

	void menu(int n) {
		switch (n) {
		case 1: classic(); break;
		case 2: pig(); break;
		case 3: chicago(); break;
		case 4: fourDice(); break;
		default: break;
		}
	}

	void classic() {
		int n;
		const char* rules = "here's a classic version of dice\n\
There are N players, each of them have K dice.\n\
Every turn they roll their dice and their points increase by rolled sum.\n\
After L turned the game ends. The one with the most points wins.";
	}


}
