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
		const char* rules = "here's a classic version of dice\n\
There are N players, each of them have K dice.\n\
Every turn they roll their dice and their points increase by rolled sum.\n\
After L turned the game ends. The one with the most points wins.";
		const char* n_getter = "now enter N (the number of players).";
		const char* k_getter = "now enter the number of dice each player will have (K).\n\
Note that it should be at least 1.";
		const char* l_getter = "now enter the number of turnes in the game. It also should be positive.\n";
		int n, k, l;
		print(rules);
		do {
			print(n_getter);
			input(n);
			print(k_getter);
			input(k);
			print(l_getter);
			input(l);
			if (n < -1 || k < 1 || l < 1) print("something's wrong. Try again");
		} while (n < -1 || k < 1 || l < 1);
		Player* players = new Player[n];
		for (int i = 0; i < n; i++) players[i] = Player(k, i);
		for (int i = 0; i < l; i++) {
			std::cout << "turn " << i + 1 << std::endl;
			for (int j = 0; j < n; j++) {
				players[j].roll();
				players[j].update();
				std::cout << players[j];
			}
			print("turn over");
			system("pause");
			std::cin.get();
		}
		results(players, n);
		delete[] players;
	}

	void pig() {
		const char* rules = "Every player has only one dice. \n\
He rolls the dice until his sum becomes 100 (win) or he gets 1 on the dice.\n\
In the last case, the player's total points are canceled and the move passes to the next player";
		const char* n_getter = "Enter the number of players (it should be at least 2)";
		print(rules);
		print(n_getter);
		int n;
		do {
			input(n);
			if (n < 2) print("something's wrong, try again");
		} while (n < 2);
		Player* players = new Player[n];
		for (int i = 0; i < n; i++) players[i] = Player(1, i);
		int curr = 0;
		do {
			players[curr].roll();
			players[curr].update();
			std::cout << players[curr] << std::endl;
			if (players[curr].sum() == 1) {
				curr = (curr + 1) % n;
				players[curr].reset();
			}
		} while (players[curr].getPts() < 100);
		std::cout << "congrats to player " << players[curr].getId() << std::endl;
		delete[] players;
	}

	void fourDice() {
		const char* rules = "Every player has 4 dice. He rolls his dice and if he has at least one six, he wins.\n\
If not, he loses.";
		const char* n_getter = "Enter number of players. Remember it should be at least 2";
		int n;
		print(rules);
		print(n_getter);
		do {
			input(n);
			if (n < 2) print("something's wrong, try again");
		} while (n < 2);
		Player* players = new Player[n];
		for (int i = 0; i < n; i++) players[i] = Player(4, i);
		for (int i = 0; i < n; i++) {
			players[i].roll();
			std::cout << players[i] << std::endl;
			if (players[i].check(6)) print("Winner!");
			else print("Loser!");
		}
		delete[] players;
	}

	void chicago() {
		const char* rules = "There are 11 turnes and 2 dice.\n\
The goal is to get number N+1, where N is a number of the turn.\n\
The first one who does this gets N+1 points.\n\
The winner is the one who has the most points after 11 turnes";
		const char* n_getter = "Enter the number of playes (at least 2)";
		print(rules);
		print(n_getter);
		int n;
		do {
			input(n);
			if (n < 2) print("something's wrong, try again");
		} while (n < 2);
		Player* players = new Player[n];
		for (int i = 0; i < n; i++) players[i] = Player(2, i);
		for (int i = 1; i < 12; i++) {
			int curr = -1;
			do {
				curr = (curr + 1) % n;
				players[curr].roll(); 
				std::cout << players[curr] << std::endl;
			} while (players[curr].sum() != i + 1);
			players[curr].update();
		}
		results(players, n);
		delete[] players;
	}

	void results(const Player* players, int n) {
			int max = 0, winner = 0;
			for (int i = 0; i < n; i++) {
				if (players[i].getPts() > max) {
					max = players[i].getPts();
					winner = i;
				}
			}
			std::cout << "Congrats to player " << players[winner].getId() << "\nScore: " << players[winner].getPts() << std::endl;
	}


}
