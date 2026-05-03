#ifndef MAP_H
#define MAP_H
#include <vector>

class Cell;
class Player;

class Map {
private:
	std::vector<Cell*> gameMap;

public:
	Map();
	~Map();

	int getSize();

	Cell* getCell(int) const;
	
	void setOwner(int index, int player);

	void drawMap(const Player p[], const int playerCount) const;
};

#endif