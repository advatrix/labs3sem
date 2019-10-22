#pragma once
#include "labslib.h"
#include "dice_dynamic_lib.h"
namespace game {
	class Player {
	private:
		int pts_;
		DiceDyn::Dice dice;
		int id_;
	public:
		Player() :pts_(0), dice(), id_(-1) {}
		Player(int n) : pts_(0), id_(-1), dice(n, nullptr) {}
		Player(int n, int id);
		inline int getPts() const { return pts_; }
		inline void roll() { dice.roll(); }
		inline void addDice(DiceDyn::Dice& other) { dice += other; }
		inline void removeDice(DiceDyn::Dice& other) { dice -= other; }
		inline void update() { pts_ += dice.sum(); }
		inline void reset() { pts_ = 0; }
		inline int getId() const { return id_; }
		inline int sum() { return dice.sum(); }
		bool check (int pts) const;
		inline int n() const { return dice.getN(); }
		friend std::ostream& operator <<(std::ostream&, const Player&);
	};
}

