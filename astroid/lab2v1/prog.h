#pragma once
#include <cmath>
#include <iostream>
#include <iomanip>

#include "Astroid.h"

#define PRECISION 6


namespace prog {
	void print(astroid::Astroid);
	
	void print(const char* msg);

	void print(astroid::Point p);

	void print(double d, int p);

	template<class T>
	void print(T a) {
		std::cout << a << std::endl;
	}

	double degreesToRadians(double t);


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

	int dialog();

	void menu(int, astroid::Astroid &);



}