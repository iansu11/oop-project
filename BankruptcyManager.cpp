#include "BankruptcyManager.h"
#include <iostream>
using namespace std;

void checkBankruptcy(Player& currentPlayer, Map& myMap) {
	while (currentPlayer.getMoney() < 0) {
		cout << endl << "警告！！" << currentPlayer.getName() << " 目前負債 " << currentPlayer.getMoney() << " 元！" << endl;

		if (currentPlayer.getOwnedLandCount() > 0) {
			cout << "請選擇要賣的土地來還債 (輸入土地編號): " << endl;
			currentPlayer.printSellLands(myMap);
			int landChoice;
			while (true) {
				cin >> landChoice;
				if (landChoice > 0 && landChoice <= currentPlayer.getOwnedLandCount()) {
					int realLandId = currentPlayer.getOwnedLandID(landChoice - 1);
					Cell& landToSell = myMap.getCell(realLandId);

					currentPlayer.sellLand(realLandId, landToSell.getSellPrice());
					myMap.setOwner(realLandId, -1); // 土地變成無主
					landToSell.resetHouse();

					cout << "已賣出 " << landToSell.getName() << "，獲得 " << landToSell.getSellPrice() << " 元" << endl;
					cout << "目前剩餘金額: " << currentPlayer.getMoney() << " 元" << endl;
					break;
				}
				else {
					cout << "無效的土地選擇，請重新輸入。" << endl;
				}
			}
		}
		else {
			cout << currentPlayer.getName() << " 已經沒有任何土地可以賣了！宣告破產！" << endl;
			currentPlayer.setBankruptcy(1);
			break;
		}
	}

}
	