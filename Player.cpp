#include "Player.h"
#include <iostream>
#include <vector>
using std::cout; using std::endl;

Player::Player() {
	money = 20000;
	position = 0;
	prison = false;
	bankruptcy = false;
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

void Player::setBankruptcy(int b) {
	bankruptcy = b;
}

int Player::getBankruptcy() {
	return bankruptcy;
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

void Player::printOwnedLands(Map& mainMap) {
	if (ownedLands.empty()) {
		cout << "目前名下沒有任何房產。" << endl;
	}

	else {
		cout << "所擁有的土地:"<<endl;
		for (int i = 0;i < ownedLands.size();i++) {
			Cell& landed = mainMap.getCell(ownedLands[i]);
			cout << i+1 << ": " << landed.getName() << endl;
		}
	}
}
