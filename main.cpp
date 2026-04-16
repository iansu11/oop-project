#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <conio.h> // 用於 _getch() 函數
#include <windows.h> // 使用 Sleep()
#include "Player.h"
#include "Dice.h"
#include "Cell.h"
#include "Map.h"
#include "UI.h"
using namespace std;

int main() {
	srand(time(0));

	Map myMap;                    
	Player p[5];
	Dice dice;                     
	int players;

	cout << "請輸入玩家人數 (2-4): ";
	cin >> players;

	while (players > 4 || players < 2) {
		cout << "玩家人數必須在 2 到 4 之間，請重新輸入: ";
		cin >> players;
	}

	for (int i = 1;i <= players;i++) {
		string name;
		cout << "請依序輸入"<<i<<"號玩家名稱(P"<<i<<"):";
		cin >> name;
		p[i].setName(name);
	}

	cout << endl << "==== 遊戲開始 ====" << endl;
	cout << "地圖總共有 " << myMap.getSize() << " 格" << endl;
	cout << "玩家 " << p[1].getName() << " 準備出發！" << endl;
	cout << endl << endl;


	// 回合開始
	for (int turn = 1; turn <= 15; turn++) {
		Sleep(500);
		cout << "[第 " << turn << " 回合]" << endl;

		for (int i = 1; i <= players; i++) {
			cout << "輪到玩家 P" << i << ":"<<p[i].getName() << endl;

			if (p[i].getPrison() > 0) {
				cout << "坐牢休息一次" << endl;
				p[i].setPrison(p[i].getPrison()-1);
				cout << "------------------" << endl;
				continue;
			}

			if(p[i].getBankruptcy()==1){
				cout << "已經破產了，換下一位玩家" << endl;
				cout << "------------------" << endl;
				continue;
			}

			// 步驟 A: 擲骰子
			char input;
			cout << "請按下[D]鍵 來擲骰子" << endl;

			while (true) {
				input = _getch(); // 讀取按鍵
				if (input == 'd' || input == 'D') {
					cout << " (骰子轉動中...)\n";
					Sleep(1000);
					break;
				}
			}
			
			int steps = dice.getNumber();
			cout << p[i].getName() << " 擲出了 " << steps << " 點。" << endl;

			if (p[i].getPosition() + steps > myMap.getSize()) {
				p[i].addMoney(2000);
				cout << " -> 新的一圈，獲得 2000 元！目前金額: " << p[i].getMoney() << " 元" << endl;
			}

			// 步驟 B: 計算新位置
			int currentPos = p[i].getPosition();
			int newPos = (currentPos + steps) % myMap.getSize();

			// 步驟 C: 更新玩家位置
			p[i].setPosition(newPos);

			// 步驟 D: 從地圖上取得玩家踩到的「那一格」資料
			Cell& landedCell = myMap.getCell(newPos);

			// 步驟 E: 印出結果
			cout << p[i].getName() << " 移動到了第 " << newPos << " 格: [" << landedCell.getName() << "]" << endl<<endl;

			drawMap(myMap, p, players);

			// 判斷踩到了什麼
			if (landedCell.getType() == CellType::Start) {
				cout << " -> 踩到起點！休息一下" << endl;
			}
			else if (landedCell.getType() == CellType::Land) {
				char choice;
				if (landedCell.getOwner() == -1 && p[i].getMoney() > landedCell.getPrice()) {
					cout << "["<< landedCell.getName() << "] -> 這塊土地目前沒有人擁有，價格是: " << landedCell.getPrice() << " 元" << endl;
					cout << "你目前有 " << p[i].getMoney() << " 元" << endl;
					cout << "請問需要購買這塊土地嗎？(y/n): " << endl;
					while (true) {
						choice = _getch(); // 讀取按鍵
						if (choice == 'y' || choice == 'Y') {
							cout << "已購買此土地，花了" << landedCell.getPrice() << " 元" << endl;
							p[i].payMoney(landedCell.getPrice());
							p[i].buyLand(newPos);
							myMap.setOwner(newPos, i);
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
				else if(landedCell.getOwner()!=i && landedCell.getOwner() != -1){
					cout << "目前在 [" << landedCell.getName() << "]，";
					cout << "你踩到 "<< p[landedCell.getOwner()].getName()<<" 的土地了！需要支付過路費: " << landedCell.getToll() << " 元" << endl;
					p[i].payMoney(landedCell.getToll());
					p[landedCell.getOwner()].addMoney(landedCell.getToll());
					cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;

					while (p[i].getMoney() < 0) {
						cout << endl << "警告！！" << p[i].getName() << " 目前負債 " << p[i].getMoney() << " 元！" << endl;

						if (p[i].getOwnedLandCount() > 0) {
							cout << "請選擇要賣的土地來還債 (輸入土地編號): " << endl;
							p[i].printSellLands(myMap);
							int landChoice;
							while (true) {
								cin >> landChoice;
								if (landChoice > 0 && landChoice <= p[i].getOwnedLandCount()) {
									int realLandId = p[i].getOwnedLandID(landChoice - 1);
									Cell& landToSell = myMap.getCell(realLandId);
									
									p[i].sellLand(realLandId, landToSell.getSellPrice());
									myMap.setOwner(realLandId, -1); // 土地變成無主
									landToSell.resetHouse(); 

									cout << "已賣出 " << landToSell.getName() << "，獲得 " << landToSell.getSellPrice() << " 元" << endl;
									cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;
									break;
								}
								else {
									cout << "無效的土地選擇，請重新輸入。" << endl;
								}
							}
						}
						else {
							cout << p[i].getName() << " 已經沒有任何土地可以賣了！宣告破產！" << endl;
							p[i].setBankruptcy(1);
							break;
						}
					}
				}
				else if (landedCell.getOwner() == i) {
					int choice;
					if (p[i].getMoney() < landedCell.getHousePrice()) {
						cout << "目前在 [" << landedCell.getName() << "] " ;
						cout << "是你自己的土地，但目前金額不足興建房屋！" << endl;
						cout << "目前剩餘金額: " << p[i].getMoney() << " 元" << endl;
					}
					else if (landedCell.getHouseLevel() < 5) {
						cout << "目前在 [" << landedCell.getName() << "] ";
						cout << "是你自己的土地，請問需要興建房屋嗎？(y/n):" << endl;
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

			else if (landedCell.getType() == CellType::Jail) {
				cout << " -> 踩到監獄了！" << endl;
				p[i].setPrison(3);
			}

			else if (landedCell.getType() == CellType::PublicLand) {
				cout << "-> " << landedCell.getName() << endl;
			}

			cout << "------------------" << endl;
		}

		cout << endl;
	}

	cout << "==== 遊戲結束 ====" << endl<<endl;
	
	for (int i = 1; i <= players; i++) {
		cout << "玩家 " << p[i].getName() << " 最終金額: " << p[i].getMoney() << " 元" << endl;
		p[i].printOwnedLands(myMap);
		cout << endl;
	}

}