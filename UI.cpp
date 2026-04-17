#include "UI.h"       
#include <iostream>
#include <iomanip>    
#include <string>
using namespace std;

void drawMap(Map& myMap, Player p[], int playerCount) {
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
		Cell& landedCell = myMap.getCell(i);
		combined = "[" + landedCell.getName();

		if (landedCell.getOwner() != -1)
			combined += " P" + to_string(landedCell.getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[i] != "")
			combined += playerPlace[i];

		cout << left << setw(w) << combined;
	}
	cout << endl;

	for (int i = 0;i <= 4;i++) {
		Cell& landedCell = myMap.getCell(i);
		string houses = "", price="",all;

		for (int h = 0;h < landedCell.getHouseLevel();h++) {
			houses += "^";
		}
		if (landedCell.getPrice() > 0) {
			price = "$" + to_string(landedCell.getPrice())+" ";
		}
		
		all=price+houses;

		cout << left << setw(w) << all;
	}
	cout << endl << endl;


	//中間左右兩側地圖印出
	for (int i = 17, j = 5; i >= 14 && j <= 8; i--, j++) {
		Cell& leftCell = myMap.getCell(i);
		combined = "[" + leftCell.getName();

		if (leftCell.getOwner() != -1)
			combined += " P" + to_string(leftCell.getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[i] != "")
			combined += playerPlace[i];

		cout << left << setw(w) << combined;

		Cell& rightCell = myMap.getCell(j);
		combined = "[" + rightCell.getName();

		if (rightCell.getOwner() != -1)
			combined += " P" + to_string(rightCell.getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[j] != "")
			combined += playerPlace[j];

		cout << setw(w3) << " " << setw(w) << combined << endl;

		//房子
		string houses = "", price="",all;

		for (int h = 0;h < leftCell.getHouseLevel();h++) {
			houses += "^";
		}
		if (leftCell.getPrice() > 0) {
			price = "$" + to_string(leftCell.getPrice()) + " ";
		}
		all = price + houses;

		cout << left << setw(w) << all;

		houses = "", price = "", all;

		for (int h = 0;h < rightCell.getHouseLevel();h++) {
			houses += "^";
		}
		if (rightCell.getPrice() > 0) {
			price = "$" + to_string(rightCell.getPrice()) + " ";
		}
		all = price + houses;

		cout << setw(w3) << " " << setw(w) << all << endl << endl;
	}

	//最底下一行地圖印出
	for (int i = 13;i >= 9;i--) {
		Cell& landedCell = myMap.getCell(i);
		combined = "[" + landedCell.getName();

		if (landedCell.getOwner() != -1)
			combined += " P" + to_string(landedCell.getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[i] != "")
			combined += playerPlace[i];

		cout << left << setw(w) << combined;
	}
	cout << endl;

	for (int i = 13;i >= 9;i--) {
		Cell& landedCell = myMap.getCell(i);
		string houses = "", price="", all;

		for (int h = 0;h < landedCell.getHouseLevel();h++) {
			houses += "^";
		}
		if (landedCell.getPrice() > 0) {
			price = "$" + to_string(landedCell.getPrice()) + " ";
		}

		all = price + houses;

		cout << left << setw(w) << all;
	}
	cout << endl << endl;
}
