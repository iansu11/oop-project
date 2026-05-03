#include "Dice.h"
#include <cstdlib>

int Dice::getNumber() {
	number = rand() % 6 + 1;
	return number;
}