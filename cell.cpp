#include "Cell.h"
using namespace std;
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
string Cell::getName() const {
	return name;
}
CellType Cell::getType() const {
	return type;
}
int Cell::getPrice() const {
	return price;
}
int Cell::getToll() const {
	if (houseLevel > 0) {
		return toll * (houseLevel + 1);
	}
	return toll;
}

int Cell::getOwner() const{
	return owner;
}

void Cell::setOwner(int player) {
	owner = player;
}

int Cell::getSellPrice() const {
	return sellPrice + (housePrice * houseLevel * 0.5);
}

void Cell::upgradeHouse() {
	houseLevel++;
}
void Cell::resetHouse() {
	houseLevel = 0;
}
int Cell::getHouseLevel() const {
	return houseLevel;
}

int Cell::getHousePrice() const {
	return housePrice;
}
