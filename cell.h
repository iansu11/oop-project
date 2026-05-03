#ifndef CELL_H
#define CELL_H
#include <string>

using std::string;
class Player;
class Map;
class CardManager;

enum class CellType {
	Start,
	Land,
	Chance,
	Fate,
	Jail,
	PublicLand,
};

class Cell {
protected:
	string name;
	CellType type;
	int price, owner,toll,sellPrice,housePrice,houseLevel;
public:
	Cell();
	Cell(string n, CellType t, int p, int to, int sell, int h);
	string getName() const;
	CellType getType() const;
	int getPrice() const;
	int getToll() const;

	int getOwner() const;
	void setOwner(int );

	int getSellPrice() const;

	void upgradeHouse();
	void resetHouse();
	int getHouseLevel() const;
	int getHousePrice() const;

	virtual void triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) {};
	virtual ~Cell() {} //虛擬解構子！
};

#endif