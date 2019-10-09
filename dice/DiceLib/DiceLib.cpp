#include "pch.h"
#include "DiceLib.h"
#include <ctime>
#include <stdexcept>

namespace dicens {
	std::ostream& Dice::print(std::ostream& s) const {
		if (!n_) s << "no dice";
		else for (int i = 0; i < n_; i++) s << points_[i] << ' ';
		s << std::endl;
		return s;
	}

	void Dice::roll() {
		srand(time(nullptr));
		for (int i = 0; i < n_; i++) points_[i] = rand() % 6 + 1;
	}

	void Dice::add(int pts) {
		if (n_ == size_) throw std::exception("group overflow");
		if (pts < 1 || pts > 6) throw std::exception("incorrect points");
		points_[n_] = pts;
		n_++;
	}

	void Dice::remove(int n) {
		if (n < 1 || n > n_) throw std::exception("invalid n");
		for (int i = n - 1; i < n_; i++) points_[i] = points_[i + 1];
		n_--;
	}

	void Dice::remove() {
		n_ = 0;
	}

	int Dice::getPts(int n) const {
		if (n < 1 || n > n_) throw std::exception( "invalid n");
		return points_[n - 1];
	}

	int Dice::sum() const {
		int s = 0;
		for (int i = 0; i < n_; i++) s += points_[i];
		return s;
	}

	bool Dice::coincidence() const {
		bool set[6] = { false, false, false, false, false, false };
		for (int i = 0; i < n_; i++) {
			if (set[points_[i]-1]) return true;
			set[points_[i]-1]++;
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
			for (int i = 0; i < n; i++) if (arr[i] < 1 || arr[i] > 6) throw std::exception("spoilt array") ;
		}
		catch (...) {
			throw std::exception("invalid array");
		}
		n_ = n;
		for (int i = 0; i < n; i++) points_[i] = arr[i];

	}
}
