#include "CardManager.h"
#include "BankruptcyManager.h"
#include <iostream>
#include <cstdlib>
#include <algorithm> //使用 std::swap 洗牌

using namespace std;

CardManager::CardManager() {
	for (int i = 1; i <= 10; i++) {
		chanceDeck.push_back(i);
		fateDeck.push_back(i);
	}
	for (int i = 0; i < 10; i++) {
		int swapIndex1 = rand() % 10;
		swap(chanceDeck[i], chanceDeck[swapIndex1]);

		int swapIndex2 = rand() % 10;
		swap(fateDeck[i], fateDeck[swapIndex2]);
	}
}
void CardManager::returnFreeJailCard() {
	chanceDeck.push_back(4);
}

void CardManager::executeChance(Player& currentPlayer, Map& gameMap, Player p[], int playerCount) {
	int card = chanceDeck[0];
	chanceDeck.erase(chanceDeck.begin());

	switch (card) {
		case 1:
			cout << "發票中獎，獲得 500 元。" << endl;
			currentPlayer.addMoney(500);
			cout << "目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			break;
		case 2:
			cout << "前往台北車站" << endl;
			if (currentPlayer.getPosition()>13) {
				currentPlayer.addMoney(2000);
				cout << " -> 新的一圈，獲得 2000 元！目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			}
			currentPlayer.setPosition(13);
			break;
		case 3:
			cout<<"醫療開銷，支付 200 元掛號費。" << endl;
			currentPlayer.payMoney(200);
			cout << "目前剩餘金額: " << currentPlayer.getMoney() << " 元" << endl;
			checkBankruptcy(currentPlayer, gameMap);
			break;
		case 4:
			cout << "免坐牢一次，可以保留使用" << endl;
			currentPlayer.setFreeJailCard(true);
			break;
		case 5:
			cout << "超速行駛，罰款 600 元" << endl;
			currentPlayer.payMoney(600);
			cout << "目前剩餘金額: " << currentPlayer.getMoney() << " 元" << endl;
			checkBankruptcy(currentPlayer, gameMap);
			break;
		case 6:
			cout << "在校表現優異，獲得獎學金 800 元" << endl;
			currentPlayer.addMoney(800);
			cout << "目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			break;
		case 7:
			cout << "在路上撿到錢包，獲得 300 元。" << endl;
			currentPlayer.addMoney(300);
			cout << "目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			break;
		case 8:
			cout << "前進3格" << endl;	
			if (currentPlayer.getPosition() + 3 > gameMap.getSize()) {
				currentPlayer.addMoney(2000);
				cout << " -> 新的一圈，獲得 2000 元！目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			}
			currentPlayer.setPosition((currentPlayer.getPosition() + 3) % gameMap.getSize());
			break;
		case 9:
			cout << "獲得銀行利息，共 400 元。" << endl;
			currentPlayer.addMoney(400);
			cout << "目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			break;
		case 10:
			cout << "獲得投資回報，獎勵 1000 元。" << endl;
			currentPlayer.addMoney(1000);
			cout << "目前金額: " << currentPlayer.getMoney() << " 元" << endl;
	}
	if (card != 4) {
		chanceDeck.push_back(card);
	}
}

void CardManager::executeFate(Player& currentPlayer, Map& gameMap, Player p[], int playerCount) {
	int card = fateDeck[0];
	fateDeck.erase(fateDeck.begin());

	switch (card) {
		case 1: {
			cout << "獲得生日獎勵，向每位玩家收取 200 元。" << endl;
			for (int j = 1; j <= playerCount; j++) {
				if (&p[j] != &currentPlayer) {
					p[j].payMoney(200);
					currentPlayer.addMoney(200);
					checkBankruptcy(p[j], gameMap);
				}
			}
			cout << "目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			break;
		}
		case 2:
			cout << "拘票，立即前往監獄，坐牢3回合。" << endl;
			currentPlayer.setPrison(3);
			currentPlayer.setPosition(4);
			break;
		case 3:
			cout<<"繳納牌照稅 500 元。" << endl;
			currentPlayer.payMoney(500);
			cout << "目前剩餘金額: " << currentPlayer.getMoney() << " 元" << endl;
			checkBankruptcy(currentPlayer, gameMap);
			break;
		case 4:
			cout << "路邊違規停車，罰款 1200 元。" << endl;
			currentPlayer.payMoney(1200);
			cout << "目前剩餘金額: " << currentPlayer.getMoney() << " 元" << endl;
			checkBankruptcy(currentPlayer, gameMap);
			break;
		case 5: {
			cout << "房屋修繕費，每一棟房子需支付 200 元維修費。" << endl;

			int totalHouses = 0;

			for (int i = 0;i < currentPlayer.getOwnedLandCount();i++) {
				int landId = currentPlayer.getOwnedLandID(i);
				Cell& landedCell = gameMap.getCell(landId);
				totalHouses += landedCell.getHouseLevel();
			}
			if (totalHouses > 0) {
				cout << "你有 " << totalHouses << " 棟房子，總共需要支付 " << totalHouses * 200 << " 元的修繕費。" << endl;
				currentPlayer.payMoney(totalHouses * 200);
				cout << "目前剩餘金額: " << currentPlayer.getMoney() << " 元" << endl;
			}
			else {
				cout << "名下沒有任何房子，不需要支付修繕費。" << endl;
				cout << "目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			}
			checkBankruptcy(currentPlayer, gameMap);
			break;
		}
		case 6:
			cout << "獲得遺產，獎勵 1500 元。" << endl;
			currentPlayer.addMoney(1500);
			cout << "目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			break;
		case 7:
			cout << "前進5格" << endl;
			if (currentPlayer.getPosition() + 5 > gameMap.getSize()) {
				currentPlayer.addMoney(2000);
				cout << " -> 新的一圈，獲得 2000 元！目前金額: " << currentPlayer.getMoney() << " 元" << endl;
			}
			currentPlayer.setPosition((currentPlayer.getPosition() + 5) % gameMap.getSize());
			break;
		case 8:
			cout << "做善事，捐款 300 元" << endl;
			currentPlayer.payMoney(300);
			cout << "目前剩餘金額: " << currentPlayer.getMoney() << " 元" << endl;
			checkBankruptcy(currentPlayer, gameMap);
			break;
		case 9:
			cout << "錢包遺失，損失 400 元。" << endl;
			currentPlayer.payMoney(400);
			cout << "目前剩餘金額: " << currentPlayer.getMoney() << " 元" << endl;
			checkBankruptcy(currentPlayer, gameMap);
			break;
		case 10:
			cout << "中樂透，獲得 1000 元。" << endl;
			currentPlayer.addMoney(1000);
			cout << "目前金額: " << currentPlayer.getMoney() << " 元" << endl;
	}

	fateDeck.push_back(card);
}