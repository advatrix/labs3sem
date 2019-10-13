#ifndef _DYCE_DYNAMIC_H_
#define _DYCE_DYNAMIC_H_

#include <iostream>

namespace DiceDyn {
	class Dice {
	private:
		int size_;
		int n_;
		int* points_;
	public:
		Dice();
		Dice(int n);
		Dice(int n, int* arr);
		void roll();
		void remove();
		int sum() const;
		bool coincidence() const;
		int getN() const { return n_; }
		int getSize() const { return size_; }
		Dice& operator + (Dice&);
		void operator += (int pts);
		void operator -= (int pts);
		int operator [](int index) const;
		friend std::ostream& operator << (std::ostream&, const Dice&);
	};
}

#endif