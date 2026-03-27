#include "Map.h"

Map::Map() {
	gameMap.push_back(Cell("Start", CellType::Start, 0));
	gameMap.push_back(Cell("Land1", CellType::Land, 200));
	gameMap.push_back(Cell("Land2", CellType::Land, 300));
	gameMap.push_back(Cell("Jail", CellType::Jail, 0));
	gameMap.push_back(Cell("Land3", CellType::Land, 400));
	gameMap.push_back(Cell("Land4", CellType::Land, 500));
}

int Map::getSize() {
	return gameMap.size();
}

Cell& Map::getCell(int index) {
	return gameMap[index];
}