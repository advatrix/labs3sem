#include "pch.h"
#include "framework.h"
#include "dice_dynamic_lib.h"
#include <ctime>

namespace DiceDyn {
	void Dice::operator += (int pts) {
		if (pts < 1 || pts > 6) throw std::exception("incorrect points");
		if (n_ >= size_) {
			size_++;
			int* old = points_;
			points_ = new int[size_];
			for (int i = 0; i < size_ - 1; i++) points_[i] = old[i];
			delete[] old;
		}
		points_[n_] = pts;
		n_++;
	}

	void Dice::operator -= (int pts) {
		int j = 0;
		for (int i = 0; i < n_; i++) if (points_[i] != pts) points_[j++] = points_[i];
		n_ = j;
	}

	int Dice::operator [](int index) const {
		if (index < 0 || index > n_ - 1) throw std::exception("incorrect index");
		return points_[index];
	}

	Dice& Dice::operator + (Dice& other) {
		if (n_ + other.getN() > size_) {
			size_ = n_ + other.getN();
			int old_n = n_;
			n_ = size_;
			int* old = points_;
			points_ = new int[size_];
			for (int i = 0; i < n_; i++) {
				if (i < old_n) points_[i] = old[i];
				else points_[i] = other[i - old_n];
			}
			delete[] old;
		}
		else {
			int old_n = n_;
			n_ += other.getN();
			for (int i = old_n; i < n_; i++) points_[i] = other[i - old_n];
		}
		return *this;
	}

	std::ostream& operator << (std::ostream& s, const Dice& dice) {
		if (!dice.n_) s << "no dice";
		else for (int i = 0; i < dice.n_; i++) s << dice.points_[i] << ' ';
		s << std::endl;
		return s;
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
		if (n < 0) throw std::exception("illegal n");
		srand(time(nullptr));
		n_ = n;
		size_ = n;
		points_ = new int[n];
		for (int i = 0; i < n; i++) points_[i] = rand() % 6 + 1;
	}

	Dice::Dice(int n, int* arr) {
		if (n < 0) throw std::exception("illegal n");
		if (n && !arr) throw std::exception("array nullptr");
		try {
			for (int i = 0; i < n; i++) if (arr[i] < 1 || arr[i] > 6) throw std::exception("spoilt array");
		}
		catch (...) {
			throw std::exception("invalid array");
		}
		n_ = n;
		size_ = n;
		points_ = new int[n];
		for (int i = 0; i < n; i++) points_[i] = arr[i];
	}

	void Dice::remove() {
		n_ = 0;
	}

	void Dice::roll() {
		srand(time(nullptr));
		for (int i = 0; i < n_; i++) points_[i] = rand() % 6 + 1;
	}
}