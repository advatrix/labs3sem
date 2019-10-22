#include "Player.h"

namespace game {
	bool Player::check(int pts) const {
		if (pts < 1 || pts > 6) return false;
		int m = n();
		for (int i = 0; i < m; i++) if (dice[i] == pts) return true;
		return false;
	}

	Player::Player(int n, int id) {
		pts_ = 0;
		dice = DiceDyn::Dice(n, nullptr);
		id_ = id;
	}

	std::ostream& operator << (std::ostream& s, const Player& p) {
		std::cout << "Player " << p.id_ << "\n" << p.dice << "\nPts: " << p.pts_ << std::endl;
		return s;
	}
}
