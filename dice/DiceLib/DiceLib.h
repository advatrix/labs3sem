#ifndef _DICE_H_
#define _DICE_H_

#include <iostream>
namespace dicens {
	class Dice
	{
	private:
		static const int size_ = 10;
		int n_;
		int points_[size_];
	public:
		Dice();
		Dice(int n);
		Dice(int n, int* arr);
		std::ostream& print(std::ostream&) const;
		void roll();
		void add(int pts);
		void remove(int n);
		void remove();
		int getPts(int n) const;
		int sum() const;
		bool coincidence() const;
		int getN() const { return n_; }
		int getMaxSize() const { return size_; }
	};
}
#endif

