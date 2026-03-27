#include "Cell.h"
using std::string;

Cell::Cell(string n, CellType t, int p) {
	name = n;
	type = t;
	price = p;
	owner = -1;
}
string Cell::getName() {
	return name;
}
CellType Cell::getType() {
	return type;
}
int Cell::getPrice() {
	return price;
}
int Cell::getOwner() {
	return owner;
}

void Cell::setowner(int owner0) {
	owner = owner0;
}