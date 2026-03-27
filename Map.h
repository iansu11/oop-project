#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Cell.h"

class Map {
private:
	std::vector<Cell> gameMap;

public:
	Map();

	int getSize();

	Cell& getCell(int);


};

#endif