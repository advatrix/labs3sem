#pragma once
#include "labslib.h"
#include "dice_dynamic_lib.h"
namespace game {
	class Player {
	private:
		int pts_;
		DiceDyn::Dice dice;
	public:
		Player() :pts_(0), dice() {}
		Player(int n) : pts_(0), dice(n, nullptr) {}
		inline int getPts() const { return pts_; }
		inline void roll() { dice.roll(); }
		inline void addDice(DiceDyn::Dice& other) { dice += other; }
		inline void removeDice(DiceDyn::Dice& other) { dice -= other; }
		inline void update() { pts_ += dice.sum(); }
		inline void reset() { pts_ = 0; }
		inline int sum() { return dice.sum(); }
		bool check(int pts);
		inline int n() { return dice.getN(); }
	};
}

