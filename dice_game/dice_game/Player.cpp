#include "Player.h"

namespace game {
	bool Player::check(int pts) {
		if (pts < 1 || pts > 6) return false;
		int m = n();
		for (int i = 0; i < m; i++) if (dice[i] == pts) return true;
		return false;
	}
}
