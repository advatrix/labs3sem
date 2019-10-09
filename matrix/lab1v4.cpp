#include <iostream>
#include "prog.h"

using namespace prog;

int main() {
	int d = 0;
	int mode = 0;
	int c = 0;
	do {
		SparseMatrix mx = { 0, 0, nullptr };
		mode = menu();
		do {
			c = create(mx, mode);
		} while (c);
		print("source matrix");
		print(mx);
		Vector b = form(mx);
		print("vector");
		print(b);
		erase(b);
		erase(mx);
		print("enter 0 to exit");
		input(d);
	} while (d);
	return 0;
}