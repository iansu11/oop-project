#include "UI.h"       
#include <iostream>
#include <iomanip>    
#include <string>
using namespace std;

void drawMap(Map& myMap, Player p[], int playerCount) {
	string combined;
	string playerPlace[16] = {};
	int const w = 23, w3 = 69;

	for (int i = 0;i < 16;i++) {
		for (int j = 1;j <= playerCount;j++) {
			if (p[j].getPosition() == i) {
				playerPlace[i] += " P" + to_string(j);
			}
		}
	}

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
	cout << endl << endl;


	for (int i = 15, j = 5; i >= 13 && j <= 7; i--, j++) {
		Cell& rightCell = myMap.getCell(i);
		combined = "[" + rightCell.getName();

		if (rightCell.getOwner() != -1)
			combined += " P" + to_string(rightCell.getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[i] != "")
			combined += playerPlace[i];

		cout << left << setw(w) << combined;

		Cell& leftCell = myMap.getCell(j);
		combined = "[" + leftCell.getName();

		if (leftCell.getOwner() != -1)
			combined += " P" + to_string(leftCell.getOwner()) + "]";
		else
			combined += "]";

		if (playerPlace[j] != "")
			combined += playerPlace[j];

		cout << setw(w3) << " " << setw(w) << combined << endl << endl;

	}


	for (int i = 12;i >= 8;i--) {
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
	cout << endl << endl;

}
