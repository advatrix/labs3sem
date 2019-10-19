#ifndef _DYCE_DYNAMIC_H_
#define _DYCE_DYNAMIC_H_

#include <iostream>

namespace DiceDyn {
	class Dice {
	private:
		int size_;
		int n_;
		int* points_; //int -> enum //
	public:
		Dice();
		Dice(int n);
		Dice(int n, const int* arr);
		Dice(const Dice& ob);
		Dice(Dice&& other) noexcept;
		void roll();
		void remove();
		int sum() const;
		bool coincidence() const;
		inline int getN() const { return n_; }
		inline int getSize() const { return size_; }
		friend Dice& operator + (const Dice&, const Dice&); // friend
		Dice& operator += (const Dice& other); //A+=B+=C;
		Dice& operator -= (const Dice& other); //A+=B+=C;
		int operator [](int index) const;
		friend std::ostream& operator << (std::ostream&, const Dice&); //>>?
		friend std::istream& operator >> (std::istream&, Dice&);
		Dice& operator = (const Dice& other);
		Dice& operator = (Dice&& other) noexcept;
		~Dice() { if (points_) delete[] points_; }
		
	};
}

#endif