#include "pch.h"
#include "../astroidProg/Astroid.cpp"
#include <tchar.h>


TEST(astroidConstructor, defaultConstructor) {
	astroid::Astroid a;
	ASSERT_EQ(a.get().x, 1);
	ASSERT_EQ(a.get().y, 4);
}

TEST(astroidConstructor, initConstructor1) {
	astroid::Astroid a(2);
	ASSERT_EQ(a.get().x, 2);
	ASSERT_EQ(a.get().y, 8);
}

TEST(astroidConstructor, initConstructor2) {
	astroid::Astroid a(10.5);
	ASSERT_EQ(a.get().x, 10.5);
	ASSERT_EQ(a.get().y, 42);
}

TEST(astroidConstructor, zeroConstructor) {
	astroid::Astroid a(0);
	ASSERT_EQ(a.get().x, 0);
	ASSERT_EQ(a.get().y, 0);
}

TEST(astroidConstructor, negativeConstructor) {
	ASSERT_THROW(astroid::Astroid a(-3), std::exception);
}

TEST(astroidSetter, set) {
	astroid::Astroid a;
	a.set(5);
	ASSERT_EQ(a.get().x, 5);
	ASSERT_EQ(a.get().y, 20);
	a.set(0);
	ASSERT_EQ(a.get().x, 0);
	ASSERT_EQ(a.get().y, 0); 
	a.set(2.5);
	ASSERT_EQ(a.get().x, 2.5);
	ASSERT_EQ(a.get().y, 10);
	ASSERT_ANY_THROW(a.set(-6));
}

TEST(length, defaultConstructor) {
	astroid::Astroid a;
	ASSERT_EQ(a.length(), 24);
}

TEST(length, a2) {
	astroid::Astroid a(2);
	ASSERT_FLOAT_EQ(a.length(), 48);
}

TEST(length, a3) {
	astroid::Astroid a(3);
	ASSERT_FLOAT_EQ(a.length(), 72);
}

TEST(length, a0) {
	astroid::Astroid a(0);
	ASSERT_FLOAT_EQ(a.length(), 0);
}

TEST(length, a13_33) {
	astroid::Astroid a(13.33);
	ASSERT_FLOAT_EQ(a.length(), 319.92);
}

TEST(length, aPI) {
	astroid::Astroid a(acos(-1));
	ASSERT_FLOAT_EQ(a.length(), 75.3982);
}

TEST(anglength, default_0) {
	astroid::Astroid a;
	ASSERT_FLOAT_EQ(a.length(0), 0);
}

TEST(anglength, default_PI_4) {
	astroid::Astroid a;
	ASSERT_NEAR(a.length(3.14159/4), 3, 0.01);
}

TEST(anglength, default_PI_2) {
	astroid::Astroid a;
	ASSERT_NEAR(a.length((acos(-1))/2), 6, 0.01);
}

TEST(anglength, default_PI) {
	astroid::Astroid a;
	ASSERT_NEAR(a.length(acos(-1)), 12, 0.01);
}

TEST(anglength, default_2PI) {
	astroid::Astroid a;
	ASSERT_NEAR(a.length(acos(-1) * 2), 24, 0.01);
}

TEST(anglength, default_BIG) {
	astroid::Astroid a;
	ASSERT_NEAR(a.length(900), 24, 0.01);
}

TEST(anglength, defaultNegative) {
	astroid::Astroid a;
	ASSERT_NEAR(a.length(-9), 0, 0.01);
}

TEST(anglength, twice_PI) {
	astroid::Astroid a(2);
	ASSERT_NEAR(a.length(acos(-1)), 24, 0.01);
}

TEST(curvatureRa, default_0) {
	astroid::Astroid a;
	ASSERT_NEAR(a.curvatureRa(0), 0, 0.01);
}

TEST(curvatureRa, default_PI_4) {
	astroid::Astroid a;
	ASSERT_NEAR(a.curvatureRa(acos(-1)/4), 6, 0.01);
}

TEST(curvatureRa, default_PI_2) {
	astroid::Astroid a;
	ASSERT_NEAR(a.curvatureRa(acos(-1)/2), 0, 0.01);
}

TEST(curvatureRa, default_MINUS_PI_4) {
	astroid::Astroid a;
	ASSERT_NEAR(a.curvatureRa(-acos(-1) / 4), 6, 0.01);
}


TEST(area, default_) {
	astroid::Astroid a;
	ASSERT_NEAR(a.s(), 18.85, 0.01);
}


TEST(curvatureRa, twice) {
	astroid::Astroid a(2);
	ASSERT_NEAR(a.s(), 37.7, 0.01);
}


TEST(cords, default_0) {
	astroid::Astroid a;
	astroid::Point p = a.cords(0);
	ASSERT_NEAR(p.x, 4, 0.01);
	ASSERT_NEAR(p.y, 0, 0.01);
}

TEST(cords, default_PI_4) {
	astroid::Astroid a;
	astroid::Point p = a.cords(acos(-1)/4);
	ASSERT_NEAR(p.x, p.y, 0.01);
	ASSERT_NEAR(p.y, sqrt(2), 0.01);
}

TEST(cords, default_PI_2) {
	astroid::Astroid a;
	astroid::Point p = a.cords(acos(-1) / 2);
	ASSERT_NEAR(p.x, 0, 0.01);
	ASSERT_NEAR(p.y, 4, 0.01);
}

TEST(cords, default_PI) {
	astroid::Astroid a;
	astroid::Point p = a.cords(acos(-1));
	ASSERT_NEAR(p.x, -4, 0.01);
	ASSERT_NEAR(p.y, 0, 0.01);
}

TEST(cords, default_2PI) {
	astroid::Astroid a;
	astroid::Point p = a.cords(2 * acos(-1));
	ASSERT_NEAR(p.x, 4, 0.01);
	ASSERT_NEAR(p.y, 0, 0.01);
}

TEST(y, default_0) {
	astroid::Astroid a;
	astroid::Point p = a.y(0);
	ASSERT_EQ(p.x, 4);
	ASSERT_EQ(p.y, -4);
}

TEST(y, default_4) {
	astroid::Astroid a;
	astroid::Point p = a.y(4);
	ASSERT_EQ(p.y, 0);
	ASSERT_EQ(p.x, 0);
}

TEST(y, default_sqrt_2) {
	astroid::Astroid a;
	astroid::Point p = a.y(sqrt(2));
	ASSERT_NEAR(p.x, sqrt(2), 0.01);
	ASSERT_NEAR(p.y, -sqrt(2), 0.01);
}

TEST(y, astr2_0) {
	astroid::Astroid a(2);
	astroid::Point p = a.y(0);
	ASSERT_NEAR(p.x, 8, 0.01);
	ASSERT_NEAR(p.y, -8, 0.01);
}

TEST(y, astr2_4) {
	astroid::Astroid a(2);
	astroid::Point p = a.y(4);
	ASSERT_NEAR(p.x, 1.8, 0.01);
	ASSERT_NEAR(p.y, -1.8, 0.01);
}

TEST(y, astr2_100) {
	astroid::Astroid a(2);
	ASSERT_ANY_THROW(astroid::Point p = a.y(100));
}

TEST(y, default_bad_x) {
	astroid::Astroid a;
	ASSERT_THROW(a.y(-8), std::exception);
}


int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}