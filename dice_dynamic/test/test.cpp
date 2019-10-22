#include "pch.h"
#include "dice_dynamic_lib.h"
#include <tchar.h>

using namespace DiceDyn;

TEST(defaultConstructor, defaultConstructor) {
	Dice dice;
	ASSERT_EQ(dice.getN(), 2);
	ASSERT_NO_THROW(dice[0]);
	ASSERT_NO_THROW(dice[1]);
	ASSERT_EQ(((dice[0] < 7) && (dice[0] > 0)), true);
	ASSERT_EQ(((dice[1] < 7) && (dice[1] > 0)), true);
	ASSERT_THROW(dice[3], std::exception);
}

TEST(initconstructor1, normalN) {
	Dice dice(4);
	ASSERT_EQ(dice.getN(), 1);
	ASSERT_EQ(dice[0], 4);
}

TEST(initconstructor1, negativeN) {
	ASSERT_THROW(Dice dice(-9), std::exception);
	try {
		Dice dice(-9);
	}
	catch (std::exception e) {
		ASSERT_EQ(strcmp(e.what(), "incorrect dice\0"), 0);
	}
}

TEST(initConstructor1, zero) {
	ASSERT_THROW(Dice dice(-9), std::exception);
	try {
		Dice dice(-9);
	}
	catch (std::exception e) {
		ASSERT_EQ(strcmp(e.what(), "incorrect dice\0"), 0);
	}
}

TEST(initConstructor2, defaultConstructor) {
	int array[] = { 1, 2, 3 };
	Dice dice(3, array);
	ASSERT_EQ(dice.getN(), 3);
	ASSERT_EQ(dice[0], 1);
	ASSERT_EQ(dice[1], 2);
	ASSERT_EQ(dice[2], 3);
	ASSERT_THROW(dice[3], std::exception);
}

TEST(initConstructor2, negativeN) {
	int array[] = { 1 };
	ASSERT_THROW(Dice dice(-3, array), std::exception);
	try {
		Dice dice(-3, array);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "illegal n\0"), 0);
	}
}

TEST(initConstructor2, incorrectPtsArray) {
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ASSERT_THROW(Dice dice(9, array), std::exception);
	try {
		Dice dice(9, array);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "invalid array\0"), 0);
	}
}

TEST(initConstructor2, nLessThanArrayLength) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(2, array);
	ASSERT_EQ(dice.getN(), 2);
	ASSERT_NO_THROW(dice[0]);
	ASSERT_NO_THROW(dice[1]);
	ASSERT_THROW(dice[2], std::exception);
}

TEST(initConstructor2, nMoreThanArrayLength) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	ASSERT_THROW(Dice dice(8, array), std::exception);
	try {
		Dice dice(8, array);
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "invalid array\0"), 0);
	}
}

TEST(initConstructor2, zeroN) {
	Dice dice(0, nullptr);
	ASSERT_EQ(dice.getN(), 0);
	ASSERT_THROW(dice[0], std::exception);
}

TEST(initConstructor2, nAndNullptr) {
	ASSERT_NO_THROW(Dice dice(2, nullptr));
	Dice dice(2, nullptr);
	ASSERT_EQ(dice.getN(), 2);
	ASSERT_EQ(dice.getSize(), 2);
}

TEST(add, normal) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	dice += 2;
	ASSERT_EQ(dice.getN(), 7);
	ASSERT_EQ(dice[6], 2);
}

TEST(add, tooBig) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	ASSERT_THROW(dice += 8, std::exception);
	ASSERT_EQ(dice.getN(), 6);
	try {
		dice += 8;
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "incorrect dice\0"), 0);
	}
}

TEST(add, tooSmall) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	ASSERT_THROW(dice += 0, std::exception);
	ASSERT_EQ(dice.getN(), 6);
	try {
		dice += 0;
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "incorrect dice"), 0);
	}
}


TEST(plusOverload, dice_int) {
	Dice dice;
	Dice dice1 = dice + 1;
	ASSERT_EQ(dice1.getN(), 3);
	ASSERT_EQ(dice1[2], 1);
}

TEST(plusOverload, dice_dice) {
	Dice dice1, dice2;
	Dice dice = dice1 + dice2;
	ASSERT_EQ(dice.getN(), 4);
}

TEST(plusOverload, mixed) {
	Dice dice1, dice2, dice3(5), dice4(12, nullptr);
	Dice dice = dice1 + 4 + dice2 + dice3 + dice4 + 3;
	ASSERT_EQ(dice.getN(), 19);
	ASSERT_EQ(dice[2], 4);
	ASSERT_EQ(dice[18], 3);
	ASSERT_EQ(dice[5], 5);
}

TEST(plusOverload, arrays) {
	int arr1[] = { 1, 2, 3, 4, 5 };
	int arr2[] = { 6, 5, 4, 3, 2, 1 };
	Dice dice1(5, arr1), dice2(6, arr2);
	Dice dice3 = dice1 + dice2;
	ASSERT_EQ(dice1.getN(), 5);
	ASSERT_EQ(dice2.getN(), 6);
	ASSERT_EQ(dice1[0], 1);
	ASSERT_EQ(dice1[1], 2);
	ASSERT_EQ(dice1[2], 3);
	ASSERT_EQ(dice1[3], 4);
	ASSERT_EQ(dice1[4], 5);
	ASSERT_EQ(dice2[0], 6);
	ASSERT_EQ(dice2[1], 5);
	ASSERT_EQ(dice2[2], 4);
	ASSERT_EQ(dice2[3], 3);
	ASSERT_EQ(dice2[4], 2);
	ASSERT_EQ(dice2[5], 1);
	ASSERT_EQ(dice3.getN(), 11);
	ASSERT_EQ(dice3[0], 1);
	ASSERT_EQ(dice3[1], 2);
	ASSERT_EQ(dice3[2], 3);
	ASSERT_EQ(dice3[3], 4);
	ASSERT_EQ(dice3[4], 5);
	ASSERT_EQ(dice3[5], 6);
	ASSERT_EQ(dice3[6], 5);
	ASSERT_EQ(dice3[7], 4);
	ASSERT_EQ(dice3[8], 3);
	ASSERT_EQ(dice3[9], 2);
	ASSERT_EQ(dice3[10], 1);
}

TEST(remove, int) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	dice -= 3;
	ASSERT_EQ(dice.getN(), 5);
	ASSERT_EQ(dice[0], 1);
	ASSERT_EQ(dice[1], 2);
	ASSERT_EQ(dice[2], 4);
	ASSERT_EQ(dice[3], 5);
	ASSERT_EQ(dice[4], 6);
}

TEST(remove, upsentPts) {
	int arr[] = { 1, 2, 2, 3, 5, 3 };
	Dice dice(6, arr);
	dice -= 4;
	ASSERT_EQ(dice.getN(), 6);
	ASSERT_EQ(dice[0], 1);
	ASSERT_EQ(dice[1], 2);
	ASSERT_EQ(dice[2], 2);
	ASSERT_EQ(dice[3], 3);
	ASSERT_EQ(dice[4], 5);
	ASSERT_EQ(dice[5], 3);
}

TEST(memoryUsage, add_remove) {
	int arr[] = { 1, 2, 3 };
	Dice dice(3, arr);
	ASSERT_EQ(dice.getN(), 3);
	ASSERT_EQ(dice.getSize(), 3);
	dice += 5;
	ASSERT_EQ(dice.getN(), 4);
	ASSERT_EQ(dice.getSize(), 4);
	dice -= 2;
	ASSERT_EQ(dice.getN(), 3);
	ASSERT_EQ(dice.getSize(), 4);
}

TEST(removeAll, normal) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	dice.remove();
	ASSERT_EQ(dice.getN(), 0);
}

TEST(removeAll, empty) {
	Dice dice(0, nullptr);
	ASSERT_NO_THROW(dice.remove());
	ASSERT_EQ(dice.getN(), 0);
}

TEST(getPts, normal) {
	int array[] = { 1, 2, 3, 4, 5, 3 };
	Dice dice(6, array);
	ASSERT_EQ(dice[0], 1);
	ASSERT_EQ(dice[1], 2);
	ASSERT_EQ(dice[2], 3);
	ASSERT_EQ(dice[3], 4);
	ASSERT_EQ(dice[4], 5);
	ASSERT_EQ(dice[5], 3);
}

TEST(getPts, negativeN) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	ASSERT_THROW(dice[-4], std::exception);
	try {
		dice[-4];
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "incorrect index"), 0);
	}
}

TEST(getPts, tooBigN) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	ASSERT_THROW(dice[8], std::exception);
	try {
		dice[8];
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "incorrect index"), 0);
	}
}

TEST(sum, normal) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	ASSERT_EQ(dice.sum(), 21);
}

TEST(sum, add) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	dice += 4;
	ASSERT_EQ(dice.sum(), 25);
}

TEST(sum, empty) {
	Dice dice(0, nullptr);
	ASSERT_EQ(dice.sum(), 0);
}

TEST(coincidence, defaultDice) {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	Dice dice(6, array);
	ASSERT_EQ(dice.coincidence(), false);
}

TEST(coincidence, coincidence) {
	int array[] = { 1, 2, 3, 3, 5, 6 };
	Dice dice(6, array);
	ASSERT_EQ(dice.coincidence(), true);
}

TEST(meqOverload, dice_int) {
	int array[] = { 1, 2, 3, 3 };
	Dice dice(4, array);
	dice -= 3;
	ASSERT_EQ(dice.getN(), 2);
	ASSERT_EQ(dice[0], 1);
	ASSERT_EQ(dice[1], 2);
}

TEST(meqOverload, dice_dice) {
	int arr[] = { 1, 2, 3, 5, 4, 4, 3, 2, 1, 5, 4, 4, 5, 6, 5, 4, 4, 1 };
	int subarr[] = { 5, 4, 4 };
	Dice dice(18, arr), subdice(3, subarr);
	dice -= subdice;
	ASSERT_EQ(dice.getN(), 9);
	ASSERT_EQ(dice[0], 1);
	ASSERT_EQ(dice[1], 2);
	ASSERT_EQ(dice[2], 3);
	ASSERT_EQ(dice[3], 3);
	ASSERT_EQ(dice[4], 2);
	ASSERT_EQ(dice[5], 1);
	ASSERT_EQ(dice[6], 5);
	ASSERT_EQ(dice[7], 6);
	ASSERT_EQ(dice[8], 1);
	dice -= subdice;
	ASSERT_EQ(dice.getN(), 9);
}

TEST(meqOverload, chain) {
	int bigArr[] = { 1, 2, 3, 5, 4, 5, 4, 2, 3, 5, 4, 1 };
	int arr[] = { 5, 4, 6, 1 };
	int subarr[] = { 6, 1 };
	Dice bigdice(12, bigArr), dice(4, arr), subdice(2, subarr);
	bigdice -= dice -= subdice;
	ASSERT_EQ(bigdice.getN(), 6);
	ASSERT_EQ(bigdice[0], 1);
	ASSERT_EQ(bigdice[1], 2);
	ASSERT_EQ(bigdice[2], 3);
	ASSERT_EQ(bigdice[3], 2);
	ASSERT_EQ(bigdice[4], 3);
	ASSERT_EQ(bigdice[5], 1);
	ASSERT_EQ(dice.getN(), 2);
	ASSERT_EQ(dice[0], 5);
	ASSERT_EQ(dice[1], 4);
	ASSERT_EQ(subdice.getN(), 2);
	ASSERT_EQ(subdice[0], 6);
	ASSERT_EQ(subdice[1], 1);
}

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}