#include "Dice.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Dice::int getNumber() {
	srand(time(0));
	number = rand() % 6 + 1;
	return number;
}