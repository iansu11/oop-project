#ifndef CELL_H
#define CELL_H
#include <string>
using std::string;

enum class CellType {
	Start,
	Land,
	Chance,
	Jail,
};

class Cell {
private:
	string name;
	CellType type;
	int price, owner;
public:
	Cell(string n, CellType t, int p);
	string getName();
	CellType getType();
	int getPrice();
	int getOwner();

	void setowner(int owner);


};

#endif