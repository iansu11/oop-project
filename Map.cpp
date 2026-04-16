#include "Map.h"

Map::Map() {
	gameMap.push_back(Cell("起點", CellType::Start, 0,0,0,0));
	gameMap.push_back(Cell("忠孝路", CellType::Land, 1000, 60, 500, 600));
	gameMap.push_back(Cell("仁愛路", CellType::Land, 1000, 60, 500, 600));
	gameMap.push_back(Cell("信義路", CellType::Land, 1200, 80, 600, 720));
	gameMap.push_back(Cell("監獄", CellType::Jail, 0, 0, 0, 0));
	gameMap.push_back(Cell("民族路", CellType::Land, 1400, 100, 700, 840));
	gameMap.push_back(Cell("民權路", CellType::Land, 1400, 100, 700, 840));
	gameMap.push_back(Cell("民生路", CellType::Land, 1600, 120, 800, 960));
	gameMap.push_back(Cell("免費停車場", CellType::PublicLand, 0, 0, 0, 0));
	gameMap.push_back(Cell("自由路", CellType::Land, 2200, 180, 1100, 1320));
	gameMap.push_back(Cell("平等路", CellType::Land, 2200, 180, 1100, 1320));
	gameMap.push_back(Cell("博愛路", CellType::Land, 2400, 200, 1200, 1440));
	gameMap.push_back(Cell("台北車站", CellType::Land, 2000, 250, 1000, 1200));
	gameMap.push_back(Cell("中華路", CellType::Land, 3000, 260, 1500, 1800));
	gameMap.push_back(Cell("中正路", CellType::Land, 3000, 260, 1500, 1800));
	gameMap.push_back(Cell("介壽路", CellType::Land, 3200, 280, 1600, 1920));
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