#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Cell.h"
#include "Map.h"
using std::string;
using std::vector;

class Player{
private:
	string name;
	int money, position, prison;
	bool bankruptcy;
	vector<int> ownedLands;

public:
	Player();

	void setName(string n);
	string getName();
	int getMoney();

	void setPosition(int p);
	int getPosition();

	void setPrison(int );
	int getPrison();

	void setBankruptcy(bool );
	bool getBankruptcy();

	int addMoney(int amount);
	int payMoney(int amount);

	void buyLand(int landid);
	void sellLand(int landid,int price);

	int getOwnedLandCount();
	void printOwnedLands(Map& mainMap);
	int getOwnedLandID(int listIndex);
};

#endif
