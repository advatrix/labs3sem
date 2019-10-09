#include <tchar.h>
#include <iostream>
#include "Astroid.h"
#include "prog.h"


using namespace prog;

int _tmain(int argc, _TCHAR* argv[]) {
	astroid::Astroid a;
	int q = 0;
	std::setprecision(10);
	print(a);
	do {
		int	d = dialog();
		menu(d, a);
		print("continue? 0/1");
		input(q);
	} while (q);
	return 0;
}