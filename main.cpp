#include <iostream>
#include <vector>
#include "Player.h"
#include "Dice.h"
using namespace std;

int main() {
	Player p1("Alice", 1500);
	cout << p1.getName() << endl;
	cout << p1.getMoney() << endl;
	cout << p1.getPosition() << endl;

	p1.addMoney(200);
	p1.payMoney(1000);
	p1.buyLand(12);

	cout << "購買後金額: " << p1.getMoney() << endl;
	p1.sellLand(12, 800);
	cout << "賣出後金額: " << p1.getMoney() << endl;

}