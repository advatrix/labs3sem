#include <strstream>
#include "Astroid.h"


namespace astroid {

	Astroid::Astroid() {
		r = 1;
		Ra = 4;
	}

	double Astroid::length(double t) const { 
		if (t > acos(-1) * 2) return length();
		if (t < 0) return 0;
		if (t < (acos(-1))/2) return 1.5 * Ra * sin(t) * sin(t);
		if (t < acos(-1)) return length() / 4 + length(t - (acos(-1))/2);
		if (t < 3 * acos(-1) / 2) return length() / 2 + length(t - acos(-1));
		return length() * 3 / 4 + length(t - 3 * acos(-1) / 2);
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
		if (x > Ra || x < -Ra) throw std::exception("illegal x");
		double y = Ra * pow(1 - (pow(x / Ra, 2. / 3)), 3. / 2);
		return { y, -y };
	}
}
