#include "CellTypes.h"
#include "Player.h"
#include "Map.h"
#include "CardManager.h"
#include "BankruptcyManager.h"
#include <windows.h> // 使用 Sleep()
#include <conio.h> // 用於 _getch() 函數
#include <iostream>
using namespace std;

StartCell::StartCell(string n)
	: Cell(n, CellType::Start, 0, 0, 0, 0) {}

void StartCell::triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) {
	cout << " -> 踩到起點了！休息一下" << endl;
}


LandCell::LandCell(string n, int p, int to, int sell, int h)
	: Cell(n, CellType::Land, p, to, sell, h) {}

void LandCell::triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) {
	char choice;
	if (getOwner() == -1 && p[i].getMoney() > getPrice()) {
		cout << "[" << getName() << "] -> 這塊土地目前沒有人擁有，價格是: " << getPrice() << " 元" << endl;
		cout << "你目前有 " << p[i].getMoney() << " 元" << endl;
		cout << "請問需要購買這塊土地嗎？(y/n): " << endl;
		while (true) {
			choice = _getch(); // 讀取按鍵
			if (choice == 'y' || choice == 'Y') {
				cout << "已購買此土地，花了" << getPrice() << " 元" << endl;
				p[i].payMoney(getPrice());
				p[i].buyLand(loopCurrentPos);
				myMap.setOwner(loopCurrentPos, i);
				cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;
				break;
			}
			else if (choice == 'n' || choice == 'N') {
				cout << "放棄購買此土地" << endl;
				break;
			}
			else {
				cout << "請輸入 y 或 n: " << endl;
			}

		}
	}
	else if (getOwner() != i && getOwner() != -1) {
		cout << "目前在 [" << getName() << "]，";
		cout << "你踩到 " << p[getOwner()].getName() << " 的土地了！需要支付過路費: " << getToll() << " 元" << endl;
		p[i].payMoney(getToll());
		p[getOwner()].addMoney(getToll());
		cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;

		BankruptcyManager::checkBankruptcy(p[i], myMap);

	}
	else if (getOwner() == i) {
		if (p[i].getMoney() < getHousePrice()) {
			cout << "目前在 [" << getName() << "] ";
			cout << "是你自己的土地，但目前金額不足興建房屋！" << endl;
			cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;
		}
		else if (getHouseLevel() < 5) {
			cout << "目前在 [" << getName() << "] ";
			cout << "是你自己的土地，請問需要興建房屋嗎，共需要 " << getHousePrice() << " 元？(y/n): " << endl;
			while (true) {
				choice = _getch();
				if (choice == 'y' || choice == 'Y') {
					cout << "已興建房屋，花了" << getHousePrice() << " 元" << endl;
					p[i].payMoney(getHousePrice());
					upgradeHouse();
					cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;
					break;
				}
				else if (choice == 'n' || choice == 'N') {
					cout << "放棄興建房屋" << endl;
					break;
				}
				else {
					cout << "請輸入 y 或 n: " << endl;
				}
			}
		}
		else {
			cout << "目前在 [" << getName() << "] ";
			cout << "是你自己的土地，房屋已達到最高等級了！!" << endl;
		}
	}
	else {
		cout << "目前在 [" << getName() << "] 上" << endl;
		cout << "沒有人擁有這塊土地，但你的金額不足以購買！" << endl;
		cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;
	}
}


ChanceCell::ChanceCell(string n)
	: Cell(n, CellType::Chance, 0, 0, 0, 0) {
}

void ChanceCell::triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) {
	char inputc;
	cout << "[機會]" << endl;
	cout << "請按下[C]鍵 來抽機會" << endl;

	while (true) {
		inputc = _getch(); // 讀取按鍵
		if (inputc == 'c' || inputc == 'C') {
			cout << " (抽卡中...)\n";
			Sleep(100);
			break;
		}
	}
	cardAdmin.executeChance(p[i], myMap, p, players);

}


FateCell::FateCell(string n)
	: Cell(n, CellType::Fate, 0, 0, 0, 0) {
}

void FateCell::triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) {
	char inputf;
	cout << "[命運]" << endl;
	cout << "請按下[F]鍵 來抽命運" << endl;

	while (true) {
		inputf = _getch(); // 讀取按鍵
		if (inputf == 'f' || inputf == 'F') {
			cout << " (抽卡中...)\n";
			Sleep(500);
			break;
		}
	}
	cardAdmin.executeFate(p[i], myMap, p, players);

}


JailCell::JailCell(string n)
	: Cell(n, CellType::Jail, 0, 0, 0, 0) {}

void JailCell::triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) {
	cout << " -> 踩到監獄了！" << endl;
	p[i].setPrison(3);
}


PublicLandCell::PublicLandCell(string n)
	: Cell(n, CellType::PublicLand, 0, 0, 0, 0) {
}

void PublicLandCell::triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) {
	cout << " -> 踩到免費停車場！休息一下" << endl;
}
