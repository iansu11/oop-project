#include "Dice.h"
#include <iostream>

int Dice::getNumber() {
	number = rand() % 6 + 1;
	return number;
}