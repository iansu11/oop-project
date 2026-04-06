#include "Map.h"

Map::Map() {
	gameMap.push_back(Cell("Start", CellType::Start, 0,0));
	gameMap.push_back(Cell("Land1", CellType::Land, 2000, 200));
	gameMap.push_back(Cell("Land2", CellType::Land, 3000, 350));
	gameMap.push_back(Cell("Jail", CellType::Jail, 0, 0));
	gameMap.push_back(Cell("Land3", CellType::Land, 3500, 400));
	gameMap.push_back(Cell("Land4", CellType::Land, 2500, 300));
}

int Map::getSize() {
	return gameMap.size();
}

Cell& Map::getCell(int index) {
	return gameMap[index];
}

void Map::setOwner(int index, int player) {
	gameMap[index].setOwner(player);
}