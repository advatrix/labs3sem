#include <strstream>
#include "Astroid.h"


namespace astroid {
	Astroid::Astroid() {
		r = 1;
		Ra = 4;
	}
	
	Astroid::Astroid(double p) {
		if (p < 0) throw std::exception("invalid radius");
		r = p;
		Ra = 4 * p;
	}

	Astroid& Astroid::set(double p) {
		if (p < 0) throw std::exception("invalid radius");
		r = p;
		Ra = 4 * p;
		return *this;
	}

	Point Astroid::y(double x) {
		if (x > Ra || x < Ra) throw std::exception("illegal x");
		double y = Ra * pow(1 - (pow(x / Ra, 2 / 3)), 3 / 2);
		return { y, -y };
	}
}
