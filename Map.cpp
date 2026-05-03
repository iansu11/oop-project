#include "Map.h"
#include "Cell.h"
#include "Player.h"
#include "CellTypes.h"
#include <iomanip>  
#include <iostream>
#include <string>
using namespace std;

Map::Map() {
	gameMap.push_back(new StartCell("起點"));
	gameMap.push_back(new LandCell("忠孝路", 1000, 60, 500, 600));
	gameMap.push_back(new LandCell("仁愛路", 1000, 60, 500, 600));
	gameMap.push_back(new LandCell("信義路", 1200, 80, 600, 720));
	gameMap.push_back(new JailCell("監獄"));
	gameMap.push_back(new LandCell("民族路", 1400, 100, 700, 840));
	gameMap.push_back(new LandCell("民權路", 1400, 100, 700, 840));
	gameMap.push_back(new LandCell("民生路", 1600, 120, 800, 960));
	gameMap.push_back(new ChanceCell("機會"));
	gameMap.push_back(new PublicLandCell("免費停車場"));
	gameMap.push_back(new LandCell("自由路", 2200, 180, 1100, 1320));
	gameMap.push_back(new LandCell("平等路", 2200, 180, 1100, 1320));
	gameMap.push_back(new LandCell("博愛路", 2400, 200, 1200, 1440));
	gameMap.push_back(new LandCell("台北車站", 2000, 250, 1000, 1200));
	gameMap.push_back(new LandCell("中華路", 3000, 260, 1500, 1800));
	gameMap.push_back(new FateCell("命運"));
	gameMap.push_back(new LandCell("中正路", 3000, 260, 1500, 1800));
	gameMap.push_back(new LandCell("介壽路", 3200, 280, 1600, 1920));
}

Map::~Map() {
	for (int i = 0; i < gameMap.size(); ++i) {
		delete gameMap[i]; // 把每一格的記憶體都釋放掉
	}
	gameMap.clear(); // 清空 vector
}

int Map::getSize() {
	return gameMap.size();
}

Cell* Map::getCell(int index) const{
	return gameMap[index];
}

void Map::setOwner(int index, int player) {
	gameMap[index]->setOwner(player);
}

void Map::drawMap(const Player p[], const int playerCount) const {
	string combined;
	string playerPlace[18] = {};
	int const w = 23, w3 = 69;

	//尋找玩家所在的格子
	for (int i = 0;i < 18;i++) {
		for (int j = 1;j <= playerCount;j++) {
			if (p[j].getPosition() == i) {
				playerPlace[i] += " P" + to_string(j);
			}
		}
	}

	//最上面一行地圖印出
	for (int i = 0;i <= 4;i++) {
		Cell* landedCell = getCell(i);
		combined = "[" + landedCell->getName();

		if (landedCell->getOwner() != -1)
			combined += " P" + to_string(landedCell->getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[i] != "")
			combined += playerPlace[i];

		cout << left << setw(w) << combined;
	}
	cout << endl;

	for (int i = 0;i <= 4;i++) {
		Cell* landedCell = getCell(i);
		string houses = "", price = "", all;

		for (int h = 0;h < landedCell->getHouseLevel();h++) {
			houses += "^";
		}
		if (landedCell->getPrice() > 0) {
			price = "$" + to_string(landedCell->getPrice()) + " ";
		}

		all = price + houses;

		cout << left << setw(w) << all;
	}
	cout << endl << endl;


	//中間左右兩側地圖印出
	for (int i = 17, j = 5; i >= 14 && j <= 8; i--, j++) {
		Cell* leftCell = getCell(i);
		combined = "[" + leftCell->getName();

		if (leftCell->getOwner() != -1)
			combined += " P" + to_string(leftCell->getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[i] != "")
			combined += playerPlace[i];

		cout << left << setw(w) << combined;

		Cell* rightCell = getCell(j);
		combined = "[" + rightCell->getName();

		if (rightCell->getOwner() != -1)
			combined += " P" + to_string(rightCell->getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[j] != "")
			combined += playerPlace[j];

		cout << setw(w3) << " " << setw(w) << combined << endl;

		//房子
		string houses = "", price = "", all;

		for (int h = 0;h < leftCell->getHouseLevel();h++) {
			houses += "^";
		}
		if (leftCell->getPrice() > 0) {
			price = "$" + to_string(leftCell->getPrice()) + " ";
		}
		all = price + houses;

		cout << left << setw(w) << all;

		houses = "", price = "", all;

		for (int h = 0;h < rightCell->getHouseLevel();h++) {
			houses += "^";
		}
		if (rightCell->getPrice() > 0) {
			price = "$" + to_string(rightCell->getPrice()) + " ";
		}
		all = price + houses;

		cout << setw(w3) << " " << setw(w) << all << endl << endl;
	}

	//最底下一行地圖印出
	for (int i = 13;i >= 9;i--) {
		Cell* landedCell = getCell(i);
		combined = "[" + landedCell->getName();

		if (landedCell->getOwner() != -1)
			combined += " P" + to_string(landedCell->getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[i] != "")
			combined += playerPlace[i];

		cout << left << setw(w) << combined;
	}
	cout << endl;

	for (int i = 13;i >= 9;i--) {
		Cell* landedCell = getCell(i);
		string houses = "", price = "", all;

		for (int h = 0;h < landedCell->getHouseLevel();h++) {
			houses += "^";
		}
		if (landedCell->getPrice() > 0) {
			price = "$" + to_string(landedCell->getPrice()) + " ";
		}

		all = price + houses;

		cout << left << setw(w) << all;
	}
	cout << endl << endl;
}