#pragma once

namespace prog {
	struct Point {
		int i;
		int j;
		double v;
		Point* next;
	};
	struct Item {
		Point* last;
		Point* first;
	};
	
	struct SparseMatrix {
		int m;
		int n;
		Item* mx;
	};

	struct Vector {
		int n;
		double* a;
	};

	template <class T>
	int input(T& a) {
		int r = 0;
		do {
			std::cin >> a;
			if (!std::cin.good()) {
				std::cin.clear();
				while (std::cin.get() != '\n');
				r++;
			}
			else r = 0;
		} while (r);
		return r;
	}

	template<class T>
	int print(T a) {
		std::cout << a << std::endl;
		return 0;
	}

	inline int prev(int i, int max) { return i ? i - 1 : max - 1; }
	inline int check(int ind, int max) { return ind > 0 && ind <= max; };

	int create(SparseMatrix&, int mode);

	int add(SparseMatrix&, int, int);

	int print(SparseMatrix);
	int print(Vector);
	int erase(SparseMatrix&);
	int erase(Vector&);

	int menu();

	int insert(SparseMatrix&, int, int, double);
	double sum(SparseMatrix mx, int i);

	Vector form(SparseMatrix mx);
}