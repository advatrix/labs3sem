#include "pch.h"
#include "framework.h"
#include "dice_dynamic_lib.h"
#include <ctime>

namespace DiceDyn {
	Dice& Dice::operator += (const Dice& other) {
		int newSize = n_ + other.getN();
		if (newSize > size_) {
			int* tmpPoints = points_;
			points_ = new int[newSize];
			for (int i = 0; i < newSize; i++) {
				if (i < n_) points_[i] = tmpPoints[i];
				else points_[i] = other[i - n_];
			}
			n_ = newSize;
			size_ = newSize;
		}
		else {
			for (int i = n_; i < newSize; i++) points_[i] = other[i - n_];
			n_ = newSize;
		}
		return *this;
	}

	Dice& Dice::operator -= (const Dice& other) {
		int* newpts = new int[n_];
		int j = 0, otherN = other.getN(), k = 0;
		for (int i = 0; i < n_; i++) {
			if (points_[i] == other[j]) j++;
			else j = 0;
			newpts[k] = points_[i];
			if (j == otherN) { k -= j; j = 0; }
			k++;
		}
		delete[] points_;
		points_ = newpts;
		size_ = n_;
		n_ = k;
		return *this;
	}

	int Dice::operator [](int index) const {
		if (index < 0 || index > n_ - 1) throw std::exception("incorrect index");
		return points_[index];
	}

	Dice operator + (const Dice& th, const Dice& other) {
		int newSize = th.n_ + other.n_;
		int* newPoints = new int[newSize];
		for (int i = 0; i < newSize; i++) {
			if (i < th.getN()) newPoints[i] = th.points_[i];
			else newPoints[i] = other[i - th.n_];
		}
		return Dice(newSize, newPoints);
	}

	std::ostream& operator << (std::ostream& s, const Dice& dice) {
		if (!dice.n_) s << "no dice";
		else for (int i = 0; i < dice.n_; i++) s << dice.points_[i] << ' ';
		s << std::endl;
		return s;
	}

	std::istream& operator >> (std::istream& s, Dice& dice) {
		int n, tmp;
		s >> n;
		if (n < 0) s.unget();
		if (s.good()) {
			if (n > dice.n_) {
				if (dice.points_) delete[] dice.points_;
				dice.points_ = new int[n];
			}
			dice.n_ = n;
			for (int i = 0; i < n;) {
				s >> tmp;
				if (s.good()) {
					if (tmp < 1 || tmp > 6) s.unget();
					else {
						dice.points_[i] = tmp;
						i++;
					}
				}
				else s.setstate(std::ios::failbit);
			}
		}
		else s.setstate(std::ios::failbit);
		return s;
	}

	Dice::Dice(const Dice& ob) {
		srand(time(nullptr));
		n_ = ob.getN();
		size_ = n_;
		points_ = nullptr;
		if (n_) {
			points_ = new int[n_];;
			for (int i = 0; i < n_; i++) points_[i] = ob[i];
		}
	}

	Dice& Dice::operator = (const Dice& other) {
		if (this != &other) {
			delete[] points_;
			points_ = nullptr;
			size_ = n_;
			if ((n_ = other.getN())) {
				points_ = new int[n_];
				for (int i = 0; i < n_; i++) points_[i] = other[i];
			}
		}
		return *this;
	}

	Dice::Dice(Dice&& other) noexcept {
		srand(time(nullptr));
		n_ = other.getN();
		size_ = other.getSize();
		points_ = other.points_;
		other.points_ = nullptr;
	}

	Dice& Dice::operator = (Dice&& other) noexcept {
		int tn = n_, ts = size_;
		n_ = other.n_;
		size_ = other.size_;
		other.n_ = tn;
		other.size_ = ts;
		int* tptr = points_;
		points_ = other.points_;
		other.points_ = tptr;
		return *this;
	}

	int Dice::sum() const {
		int s = 0;
		for (int i = 0; i < n_; i++) s += points_[i];
		return s;
	}

	bool Dice::coincidence() const {
		bool set[6] = { false, false, false, false, false, false };
		for (int i = 0; i < n_; i++) {
			if (set[points_[i] - 1]) return true;
			set[points_[i] - 1] = true;
		}
		return false;
	}

	Dice::Dice() {
		size_ = 2;
		n_ = 2;
		points_ = new int[2];
		srand(time(nullptr));
		points_[0] = rand() % 6 + 1;
		points_[1] = rand() % 6 + 1;
	}

	Dice::Dice(int n) {
		srand(time(nullptr));
		if (n < 1 || n > 6) throw std::exception("incorrect dice");
		n_ = 1;
		size_ = 1;
		points_ = new int[1];
		points_[0] = n;
	}

	Dice::Dice(int n, const int* arr) {
		srand(time(nullptr));
		if (n < 0) throw std::exception("illegal n");
		if (arr) {
			try {
				for (int i = 0; i < n; i++) if (arr[i] < 1 || arr[i] > 6) throw std::exception("spoilt array");
			}
			catch (...) {
				throw std::exception("invalid array");
			}
		}
		n_ = n;
		size_ = n;
		points_ = new int[n];
		if(arr) for (int i = 0; i < n; i++) points_[i] = arr[i];
		else {
			srand(time(nullptr));
			for (int i = 0; i < n; i++) points_[i] = rand() % 6 + 1;
		}
	}

	void Dice::remove() {
		n_ = 0;
	}

	void Dice::roll() {

		for (int i = 0; i < n_; i++) points_[i] = rand() % 6 + 1;
	}
}