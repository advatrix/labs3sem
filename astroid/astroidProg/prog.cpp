#include <tchar.h>
#include <iostream>

#include "Astroid.h"
#include "prog.h"

namespace prog {
	int dialog() {
		print("what else?");
		print("0: quit");
		print("1: return length from angle");
		print("2: return curvature radius from angle");
		print("3: return x, y from t");
		print("4: return y from x");
		print("5: edit astroid");
		int ans = 0;
		input(ans);
		return ans;
	}

	void print(double t, int p) {
		std::cout << std::setprecision(p) << t << std::endl;
	}

	void print(astroid::Astroid a) {
		std::cout << std::setprecision(PRECISION) << "Astroid parameters: r = " << a.get().x << "\tRa = " <<
			a.get().y << "\nlength = " << a.length() << "\narea = " << a.s() << std::endl;
	}

	void print(const char* msg) {
		if (msg) std::cout << msg << std::endl;
	}

	void print(astroid::Point p) {
		std::cout << std::setprecision(PRECISION) << "x = " << p.x << "\ny = " << p.y << std::endl;
	}

	void menu(int m, astroid::Astroid& a) {
		switch (m) {
		case 0: {
			return;
		}
		case 1: {
			double t;
			print("enter angle");
			input(t);
			std::cout << std::setprecision(PRECISION) << "length = " << a.length(degreesToRadians(t)) << std::endl;
			break;
		}
		case 2: {
			double t;
			print("enter angle");
			input(t);
			std::cout << std::setprecision(PRECISION) << "curvature radius is " << a.curvatureRa(degreesToRadians(t)) << std::endl;
			break;
		}
		case 3: {
			double t;
			print("enter angle");
			input(t);
			astroid::Point p = a.cords(degreesToRadians(t));
			print(p);
			break;
		}
		case 4: {
			double x;
			print("enter x");
			input(x);
			try {
				astroid::Point y = a.y(x);
				std::cout << std::setprecision(PRECISION) << "y1 = " << y.x << "\ny2 = " << y.y << std::endl;
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			break;
		}
		case 5: {
			double newr;
			print("enter new internal radius (r)");
			input(newr);
			try {
				a.set(newr);
				print("edited successfully");
				print(a);
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			break;
		}
		default: {
			print("incorrect choice");
		}
		}
	}

	double degreesToRadians(double t) {
		return t * acos(-1) / 180.;
	}

}



