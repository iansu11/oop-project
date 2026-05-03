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
	bool bankruptcy, FreeJailCard;
	vector<int> ownedLands;

public:
	Player();

	void setName(string n);
	string getName() const;
	int getMoney() const;

	void setPosition(int p);
	int getPosition() const;

	void setPrison(int );
	int getPrison() const ;

	void setBankruptcy(bool );
	bool getBankruptcy() const;

	void setFreeJailCard(bool);
	bool getFreeJailCard() const;

	int addMoney(int amount);
	int payMoney(int amount);

	void buyLand(int landid);
	void sellLand(int landid,int price);

	int getOwnedLandCount() const;
	void printOwnedLands(const Map& mainMap) const;
	void printSellLands(const Map& mainMap) const;
	int getOwnedLandID(const int listIndex) const;

	int getTotalAssets(const Map& mainMap) const;
};

#endif
