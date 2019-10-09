#pragma once
#ifndef _ASTROID_H_
#define _ASTROID_H
#include <math.h>

namespace astroid {
	
	struct Point {
		double x;
		double y;
	};

	class Astroid {
	private:
		double r;
		double Ra;
	public:
		Astroid();
		Astroid(double p);
		Astroid& set(double r);
		Point get() const { return { r, Ra }; }
		double s() const { return 3. / 8 * acos(-1) * r * 16; }
		double length(double t) const { return 1.5 * Ra * sin(t); }
		double length() const { return 6 * Ra; }
		double curvatureRa(double t) const { return 1.5 * Ra * sin(2 * t); }
		Point cords(double t) { return { Ra * pow(sin(t),3), Ra * pow(cos(t), 3) }; }
		Point y(double x);
	};
}

#endif

