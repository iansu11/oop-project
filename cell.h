#ifndef CELL_H
#define CELL_H
#include <string>
using std::string;

enum class CellType {
	Start,
	Land,
	Chance,
	Jail,
	PublicLand,
};

class Cell {
private:
	string name;
	CellType type;
	int price, owner,toll;
public:
	Cell();
	Cell(string n, CellType t, int p, int to);
	string getName();
	CellType getType();
	int getPrice();
	int getToll();
	int getOwner();

	void setOwner(int );


};

#endif