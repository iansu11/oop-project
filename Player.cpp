#include "Player.h"
#include <iostream>
#include <vector>

Player::Player(string n0, int m0) {
	name = n0;
	money = m0;
	position = 0;
	prison = false;
	bankruptcy = false;
}

string Player::getName() {
	return name;
}

int Player::getMoney() {
	return money;
}

int Player::getPosition() {
	return position;
}

bool Player::isprison() {
	return prison;
}

bool Player::isbankruptcy() {
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

