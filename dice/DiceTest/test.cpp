#include "pch.h"
#include <tchar.h>
#include <string.h>
#include "gtest/gtest.h"
#include "DiceLib.h"


TEST(defaultConstructor, defaultConstructor) {
	dicens::Dice dice;
	ASSERT_EQ(dice.getMaxSize(), 10);
	ASSERT_EQ(dice.getN(), 2);
	ASSERT_NO_THROW(dice.getPts(1));
	ASSERT_NO_THROW(dice.getPts(2));
	ASSERT_THROW(dice.getPts(3), std::exception);
}

TEST(initconstructor1, normalN) {
	dicens::Dice dice(4);
	ASSERT_EQ(dice.getMaxSize(), 10);
	ASSERT_EQ(dice.getN(), 4);
	ASSERT_NO_THROW(dice.getPts(1));
	ASSERT_NO_THROW(dice.getPts(2));
	ASSERT_NO_THROW(dice.getPts(3));
	ASSERT_NO_THROW(dice.getPts(4));
	ASSERT_THROW(dice.getPts(5), std::exception);
}

TEST(initconstructor1, negativeN) {
	ASSERT_THROW(dicens::Dice dice(-9), std::exception);
	try {
		dicens::Dice dice(-9);
	}
	catch (std::exception e) {
		ASSERT_EQ(strcmp(e.what(), "illegal n\0"), 0);
	}
}

TEST(initConstructor1, bigN) {
	ASSERT_THROW(dicens::Dice dice(17), std::exception);
	try {
		dicens::Dice dice(-9);
	}
	catch (std::exception e) {
		ASSERT_EQ(strcmp(e.what(), "illegal n\0"), 0);
	}
}

TEST(initConstructor1, zero) {
	ASSERT_NO_THROW(dicens::Dice dice(0));
	dicens::Dice dice(0);
	ASSERT_EQ(dice.getN(), 0);
}

TEST(initConstructor2, defaultConstructor) {
	int array[] = { 1, 2, 3 };
	dicens::Dice dice(3, array);
	ASSERT_EQ(dice.getN(), 3);
	ASSERT_EQ(dice.getPts(1), 1);
	ASSERT_EQ(dice.getPts(2), 2);
	ASSERT_EQ(dice.getPts(3), 3);
	ASSERT_THROW(dice.getPts(4), std::exception);
}

TEST(initConstructor2, negativeN) {
	int array[] = {1};
	ASSERT_THROW(dicens::Dice dice(-3, array),std::exception);
	try {
		dicens::Dice dice(-3, array);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "illegal n\0"), 0);
	}
}

TEST(initConstructor2, tooBigArray) {
	int array[] = { 1, 2, 3, 4, 5, 6 , 1, 2, 3, 4, 5, 6, 1,2, 3, 4, 5, 6 };
	ASSERT_THROW(dicens::Dice dice(18, array), std::exception);
	try {
		dicens::Dice dice(18, array);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "illegal n\0"), 0);
	}
}

TEST(initConstructor2, incorrectPtsArray) {
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ASSERT_THROW(dicens::Dice dice(9, array), std::exception);
	try {
		dicens::Dice dice(9, array);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "invalid array\0"), 0);
	}
}

TEST(initConstructor2, nLessThanArrayLength) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(2, array);
	ASSERT_EQ(dice.getN(), 2);
	ASSERT_NO_THROW(dice.getPts(1));
	ASSERT_NO_THROW(dice.getPts(2));
	ASSERT_THROW(dice.getPts(3), std::exception);
}

TEST(initConstructor2, nMoreThanArrayLength) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	ASSERT_THROW(dicens::Dice dice(8, array), std::exception);
	try {
		dicens::Dice dice(8, array);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "invalid array\0"), 0);
	}
}

TEST(initConstructor2, zeroN) {
	dicens::Dice dice(0, nullptr);
	ASSERT_EQ(dice.getN(), 0);
	ASSERT_THROW(dice.getPts(1), std::exception);
}

TEST(initConstructor2, nAndNullptr) {
	ASSERT_THROW(dicens::Dice dice(2, nullptr),std::exception);
	try {
		dicens::Dice dice(2, nullptr);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "array nullptr\0"), 0);
	}
}

TEST(add, normal) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	dice.add(2);
	ASSERT_EQ(dice.getN(), 7);
	ASSERT_EQ(dice.getPts(7), 2);
}

TEST(add, tooBig) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_THROW(dice.add(8), std::exception);
	ASSERT_EQ(dice.getN(), 6);
	try {
		dice.add(8);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "incorrect points\0"), 0);
	}
}

TEST(add, tooSmall) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_THROW(dice.add(0), std::exception);
	ASSERT_EQ(dice.getN(), 6);
	try {
		dice.add(0);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "incorrect points"), 0);
	}
}

TEST(add, empty) {
	dicens::Dice dice(0);
	dice.add(2);
	ASSERT_EQ(dice.getN(), 1);
	ASSERT_EQ(dice.getPts(1), 2);
}

TEST(add, overflow) {
	int array[] = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4 };
	dicens::Dice dice(10, array);
	ASSERT_THROW(dice.add(2), std::exception);
	ASSERT_EQ(dice.getN(), 10);
	try {
		dice.add(2);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "group overflow"), 0);
	}
}

TEST(remove, normal) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	dice.remove(3);
	ASSERT_EQ(dice.getN(), 5);
	ASSERT_EQ(dice.getPts(1), 1);
	ASSERT_EQ(dice.getPts(2), 2);
	ASSERT_EQ(dice.getPts(3), 4);
	ASSERT_EQ(dice.getPts(4), 5);
	ASSERT_EQ(dice.getPts(5), 6);
}

TEST(remove, empty) {
	dicens::Dice dice(0, nullptr);
	ASSERT_THROW(dice.remove(1), std::exception);
	try {
		dice.remove(1);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "invalid n"), 0);
	}
}


TEST(remove, negativeN) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_THROW(dice.remove(-1), std::exception);
	try {
		dice.remove(-1);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "invalid n"), 0);
	}
}

TEST(remove, bigN) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_THROW(dice.remove(7), std::exception);
	try {
		dice.remove(7);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "invalid n"), 0);
	}
}

TEST(removeAll, normal) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	dice.remove();
	ASSERT_EQ(dice.getN(), 0);
}


TEST(removeAll, empty) {
	dicens::Dice dice(0, nullptr);
	ASSERT_NO_THROW(dice.remove());
	ASSERT_EQ(dice.getN(), 0);
}

TEST(getPts, normal) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_EQ(dice.getPts(1), 1);
	ASSERT_EQ(dice.getPts(2), 2);
	ASSERT_EQ(dice.getPts(3), 3);
	ASSERT_EQ(dice.getPts(4), 4);
	ASSERT_EQ(dice.getPts(5), 5);
	ASSERT_EQ(dice.getPts(6), 6);
}

TEST(getPts, negativeN) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_THROW(dice.getPts(-4), std::exception);
	try {
		dice.getPts(-4);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "invalid n"), 0);
	}
}


TEST(getPts, tooBigN) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_THROW(dice.getPts(8), std::exception);
	try {
		dice.getPts(8);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "invalid n"), 0);
	}
}

TEST(sum, normal) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_EQ(dice.sum(), 21);
}

TEST(sum, add) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	dice.add(4);
	ASSERT_EQ(dice.sum(), 25);
}

TEST(sum, empty) {
	dicens::Dice dice(0);
	ASSERT_EQ(dice.sum(), 0);
}

TEST(coincidence, defaultDice) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_EQ(dice.coincidence(), false);
}

TEST(coincidence, coincidence) {
	int array[] = { 1, 2, 3, 3, 5, 6 };
	dicens::Dice dice(6, array);
	ASSERT_EQ(dice.coincidence(), true);
}

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
