#include <iostream>
#include <vector>
#include "Player.h"
#include "Dice.h"
#include "cell.h"
using namespace std;

int main() {
	
	vector<Cell>gameMap;
	Cell c1("Start", CellType::Start, 0);
	Cell c2("Land1", CellType::Land, 200);
	Cell c3("Land2", CellType::Land, 300);
	Cell c4("Jail", CellType::Jail, 0);
	Cell c5("Land3", CellType::Land, 400);
	Cell c6("Land4", CellType::Land, 500);
	
	gameMap.push_back(c1);
	gameMap.push_back(c2);
	gameMap.push_back(c3);
	gameMap.push_back(c4);
	gameMap.push_back(c5);
	gameMap.push_back(c6);

	cout << gameMap.size();


	/*Player p1("Alice", 1500);
	cout << p1.getName() << endl;
	cout << p1.getMoney() << endl;
	cout << p1.getPosition() << endl;

	p1.addMoney(200);
	p1.payMoney(1000);
	p1.buyLand(12);

	cout << "購買後金額: " << p1.getMoney() << endl;
	p1.sellLand(12, 800);
	cout << "賣出後金額: " << p1.getMoney() << endl;*/

}