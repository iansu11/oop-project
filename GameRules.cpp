#include "GameRules.h"
#include <iostream>
#include <conio.h> // 用於 _getch() 函數
#include <windows.h> // 使用 Sleep()
#include "UI.h"
#include "BankruptcyManager.h"
#include "Map.h"
using namespace std;

void jailRule(Player& p, CardManager& cardAdmin, bool& skip) {
	if (p.getPrison() > 0) {
		if (p.getFreeJailCard() == true) {
			cout << "你有免坐牢卡，是否要使用？(y/n): " << endl;
			char choice;
			while (true) {
				choice = _getch(); // 讀取按鍵
				if (choice == 'y' || choice == 'Y') {
					cout << "使用了免坐牢卡，這回合不用坐牢了！" << endl;
					p.setFreeJailCard(false); // 使用掉免坐牢卡
					p.setPrison(0);
					cardAdmin.returnFreeJailCard();
					break;
				}
				else if (choice == 'n' || choice == 'N') {
					cout << "選擇不使用免坐牢卡，這回合照常坐牢。" << endl;
					cout << "坐牢休息一次" << endl;
					p.setPrison(p.getPrison() - 1);
					cout << "------------------" << endl;
					skip = true;
					break;
				}
				else {
					cout << "請輸入 y 或 n: " << endl;
				}
			}
		}
		else {
			cout << "坐牢休息一次" << endl;
			p.setPrison(p.getPrison() - 1);
			cout << "------------------" << endl;
			skip = true;
		}
	}
}

void executeCellAction(Player p[], int i, Map& myMap, int players, CardManager& cardAdmin) {
	while (true) {
		// 每次進迴圈，都要去抓玩家「當下最新的位置」
		int loopCurrentPos = p[i].getPosition();

		// loopCurrentPos 去地圖上抓玩家踩到的「那一格」資料
		Cell& landedCell = myMap.getCell(loopCurrentPos);

		// 印出結果
		cout << p[i].getName() << " 移動到了第 " << loopCurrentPos << " 格: [" << landedCell.getName() << "]" << endl << endl;

		drawMap(myMap, p, players);

		// 判斷踩到了什麼
		if (landedCell.getType() == CellType::Start) {
			cout << " -> 踩到起點！休息一下" << endl;
		}
		else if (landedCell.getType() == CellType::Land) {
			char choice;
			if (landedCell.getOwner() == -1 && p[i].getMoney() > landedCell.getPrice()) {
				cout << "[" << landedCell.getName() << "] -> 這塊土地目前沒有人擁有，價格是: " << landedCell.getPrice() << " 元" << endl;
				cout << "你目前有 " << p[i].getMoney() << " 元" << endl;
				cout << "請問需要購買這塊土地嗎？(y/n): " << endl;
				while (true) {
					choice = _getch(); // 讀取按鍵
					if (choice == 'y' || choice == 'Y') {
						cout << "已購買此土地，花了" << landedCell.getPrice() << " 元" << endl;
						p[i].payMoney(landedCell.getPrice());
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
			else if (landedCell.getOwner() != i && landedCell.getOwner() != -1) {
				cout << "目前在 [" << landedCell.getName() << "]，";
				cout << "你踩到 " << p[landedCell.getOwner()].getName() << " 的土地了！需要支付過路費: " << landedCell.getToll() << " 元" << endl;
				p[i].payMoney(landedCell.getToll());
				p[landedCell.getOwner()].addMoney(landedCell.getToll());
				cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;

				checkBankruptcy(p[i], myMap);

			}
			else if (landedCell.getOwner() == i) {
				if (p[i].getMoney() < landedCell.getHousePrice()) {
					cout << "目前在 [" << landedCell.getName() << "] ";
					cout << "是你自己的土地，但目前金額不足興建房屋！" << endl;
					cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;
				}
				else if (landedCell.getHouseLevel() < 5) {
					cout << "目前在 [" << landedCell.getName() << "] ";
					cout << "是你自己的土地，請問需要興建房屋嗎，共需要 " << landedCell.getHousePrice() << " 元？(y/n): " << endl;
					while (true) {
						choice = _getch();
						if (choice == 'y' || choice == 'Y') {
							cout << "已興建房屋，花了" << landedCell.getHousePrice() << " 元" << endl;
							p[i].payMoney(landedCell.getHousePrice());
							landedCell.upgradeHouse();
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
					cout << "目前在 [" << landedCell.getName() << "] ";
					cout << "是你自己的土地，房屋已達到最高等級了！!" << endl;
				}
			}
			else {
				cout << "目前在 [" << landedCell.getName() << "] 上" << endl;
			}
		}

		else if (landedCell.getType() == CellType::Chance) {
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

			//檢查抽完卡後，位置有沒有變？
			if (p[i].getPosition() != loopCurrentPos) {
				continue; // 重新判定新格子！
			}
		}
		else if (landedCell.getType() == CellType::Fate) {
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

			//檢查抽完卡後，位置有沒有變？
			if (p[i].getPosition() != loopCurrentPos) {
				continue; // 重新判定新格子！
			}
		}

		else if (landedCell.getType() == CellType::Jail) {
			cout << " -> 踩到監獄了！" << endl;
			p[i].setPrison(3);
		}

		else if (landedCell.getType() == CellType::PublicLand) {
			cout << "-> " << landedCell.getName() << endl;
		}
		break;
	}
}