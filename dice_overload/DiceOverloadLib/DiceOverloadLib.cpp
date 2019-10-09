// DiceOverloadLib.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include "DiceOverloadLib.h"
#include <ctime>

namespace DiceOL {
	void Dice::operator += (int pts) {
		if (n_ >= size_) throw std::exception("overflow");
		if (pts < 1 || pts > 6) throw std::exception("incorrect points");
		points_[n_] = pts;
		n_++;
	}

	void Dice::operator -= (int pts) {
		int j = 0;
		for (int i = 0; i < n_; i++) if (points_[i] != pts) points_[j++] = points_[i];
		n_ = j;
	}
	
	int Dice::operator [](int index) const {
		if (index < 0 || index > n_) throw std::exception("incorrect index");
		return points_[index];
	}
	
	Dice& Dice::operator + (Dice& other) {
		if (n_ + other.getN() > size_) throw std::exception("overflow");
		for (int i = 0; i < other.getN(); i++) { *this += other[i]; }
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
			set[points_[i] - 1]++;
		}
		return false;
	}

	Dice::Dice() {
		n_ = 2;
		srand(time(nullptr));
		points_[0] = rand() % 6 + 1;
		points_[1] = rand() % 6 + 1;
	}

	Dice::Dice(int n) {
		if (n < 0 || n > size_) throw std::exception("illegal n");
		srand(time(nullptr));
		n_ = n;
		for (int i = 0; i < n; i++) points_[i] = rand() % 6 + 1;
	}

	Dice::Dice(int n, int* arr) {
		if (n < 0 || n > size_) throw std::exception("illegal n");
		if (n && !arr) throw std::exception("array nullptr");
		try {
			for (int i = 0; i < n; i++) if (arr[i] < 1 || arr[i] > 6) throw std::exception("spoilt array");
		}
		catch (...) {
			throw std::exception("invalid array");
		}
		n_ = n;
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
