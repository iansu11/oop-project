#include "Cell.h"
using std::string;

Cell::Cell() {
	name = "";
	type = CellType::Start;
	price = 0;
	toll = 0;
	sellPrice = 0;
	housePrice = 0;
	houseLevel = 0;
	owner = -1;
}

Cell::Cell(string n, CellType ty, int p, int to,int sell, int h) {
	name = n;
	type = ty;
	price = p;
	toll = to;
	sellPrice = sell;
	housePrice = h;
	houseLevel = 0;
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
	if (houseLevel > 0) {
		return toll * (houseLevel + 1);
	}
	return toll;
}

int Cell::getOwner() {
	return owner;
}

void Cell::setOwner(int player) {
	owner = player;
}

int Cell::getSellPrice() {
	return sellPrice + (housePrice * houseLevel * 0.5);
}

void Cell::upgradeHouse() {
	houseLevel++;
}
void Cell::resetHouse() {
	houseLevel = 0;
}
int Cell::getHouseLevel() {
	return houseLevel;
}

int Cell::getHousePrice() {
	return housePrice;
}