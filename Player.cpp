#include "Player.h"
#include <iostream>
#include <vector>
using std::cout; using std::endl;

Player::Player() {
	money = 5000;
	position = 0;
	prison = 0;
	bankruptcy = false;
	FreeJailCard = 0;
}

void Player::setName(string n) {
	name = n;
}

string Player::getName() {
	return name;
}

int Player::getMoney() {
	return money;
}

void Player::setPosition(int p) {
	position = p;
}

int Player::getPosition() {
	return position;
}

void Player::setPrison(int p) {
	prison = p;
}

int Player::getPrison() {
	return prison;
}

void Player::setBankruptcy(bool b) {
	bankruptcy = b;
}

bool Player::getBankruptcy() {
	return bankruptcy;
}

void Player::setFreeJailCard(bool j) {
	FreeJailCard = j;
}
bool Player::getFreeJailCard() {
	return FreeJailCard;
}

int Player::addMoney(int amount) {
	money += amount;
	return money;
}

int Player::payMoney(int amount) {
	money -= amount;
	return money;
}

void Player::buyLand(int landid) {
	ownedLands.push_back(landid);
}

void Player::sellLand(int landid, int price) {
	for (int i = 0; i < ownedLands.size();i++) {
		if (ownedLands[i] == landid) {
			ownedLands.erase(ownedLands.begin() + i);
			addMoney(price);
			break;
		}
	}
}

int Player::getOwnedLandCount() {
	return ownedLands.size();
}

void Player::printOwnedLands(Map& mainMap) {
	if (ownedLands.empty()) {
		cout << "目前名下沒有任何房產。" << endl;
	}

	else {
		cout << "所擁有的土地:"<<endl;
		for (int i = 0;i < ownedLands.size();i++) {
			Cell& landed = mainMap.getCell(ownedLands[i]);
			cout << i+1 << ": " << landed.getName() << "(" << landed.getPrice() << "元" ;
			if (landed.getHouseLevel() > 0) {
				cout << "，房屋*" << landed.getHouseLevel() << ")" << endl;
			}
			else {
				cout << ")" << endl;
			}
		}
	}
}

void Player::printSellLands(Map& mainMap) {
	cout << "可出售的土地:"<<endl;
	for (int i = 0;i < ownedLands.size();i++) {
		Cell& landed = mainMap.getCell(ownedLands[i]);
		cout << i+1 << ": " << landed.getName() << " (賣出價格: " << landed.getSellPrice() << " 元)"<< endl;
	}
}

int Player::getOwnedLandID(int listIndex) {
	return ownedLands[listIndex];
}

int Player::getTotalAssets(Map& mainMap) {
	int total = 0;
	for (int i = 0;i < ownedLands.size();i++) {
		Cell& landed = mainMap.getCell(ownedLands[i]);
		total += landed.getPrice() + (landed.getHouseLevel() * landed.getHousePrice());
	}
	total += money;

	return total;
}