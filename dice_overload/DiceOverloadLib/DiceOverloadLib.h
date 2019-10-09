#ifndef _DICE_OVERLOAD_LIB_H_
#define _DICE_OVERLOAD_LIB_H_

#include <iostream>

namespace DiceOL {
	class Dice {
	private:
		static const int size_ = 10;
		int n_;
		int points_[size_];
	public:
		Dice();
		Dice(int n);
		Dice(int n, int* arr);
		void roll();
		void remove();
		int sum() const;
		bool coincidence() const;
		int getN() const { return n_; }
		int getMaxSize() const { return size_; }
		Dice& operator + (Dice&);
		void operator += (int pts);
		void operator -= (int pts);
		int operator [](int index) const;
		friend std::ostream& operator << (std::ostream&, const Dice&);
	};
}

#endif
