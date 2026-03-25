#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
using std::string;
using std::vector;

class Player{
private:
	string name;
	int money,position;
	bool prison,bankruptcy;
	vector<int> ownedLands;
public:
	Player(string n0, int m0);
	string getName();
	int getMoney();
	int getPosition();
	bool isprison();
	bool isbankruptcy();

	int addMoney(int amount);
	int payMoney(int amount);

	void buyLand(int landid);
	void sellLand(int landid,int price);

};

#endif
