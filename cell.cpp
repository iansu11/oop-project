#include "Cell.h"
using std::string;

Cell::Cell() {
	name = "";
	type = CellType::Start;
	price = 0;
	toll = 0;
	sellPrice = 0;
	owner = -1;
}

Cell::Cell(string n, CellType ty, int p, int to,int sell) {
	name = n;
	type = ty;
	price = p;
	toll = to;
	sellPrice = sell;
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
int Cell::getToll() {
	return toll;
}

int Cell::getOwner() {
	return owner;
}

void Cell::setOwner(int player) {
	owner = player;
}

int Cell::getSellPrice() {
	return sellPrice;
}
