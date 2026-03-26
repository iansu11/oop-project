#include "Dice.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int Dice::getNumber() {
	srand(time(0));
	number = rand() % 6 + 1;
	return number;
}