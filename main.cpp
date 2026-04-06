#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <conio.h> // 用於 _getch() 函數
#include <windows.h> // 使用 Sleep()
#include "Player.h"
#include "Dice.h"
#include "Cell.h"
#include "Map.h"
using namespace std;

void drawMap(Map& myMap, Player p[], int playerCount) {
	string combined;

	for (int i = 0;i <= 4;i++) {
		Cell& landedCell = myMap.getCell(i);
		string combined = "[" + landedCell.getName() + "]";
		cout << left << setw(11) << combined;
	}
	cout << endl<<endl;

	Cell& landedCell = myMap.getCell(15);
	combined = "[" + landedCell.getName() + "]";
	cout << left << setw(11) << combined;
	landedCell = myMap.getCell(5);
	combined = "[" + landedCell.getName() + "]";
	cout<< setw(33) << " " << setw(11) << combined<<endl<<endl;

	landedCell = myMap.getCell(14);
	combined = "[" + landedCell.getName() + "]";
	cout << left << setw(11) << combined;
	landedCell = myMap.getCell(6);
	combined = "[" + landedCell.getName() + "]";
	cout << setw(33) << " " << setw(11) << combined << endl << endl;

	landedCell = myMap.getCell(13);
	combined = "[" + landedCell.getName() + "]";
	cout << left << setw(11) << combined;
	landedCell = myMap.getCell(7);
	combined = "[" + landedCell.getName() + "]";
	cout << setw(33) <<" " << setw(11) << combined << endl << endl;

	for (int i = 12;i >= 8;i--) {
		Cell& landedCell = myMap.getCell(i);
		combined = "[" + landedCell.getName() + "]";
		cout << left << setw(11) << combined;
	}
	cout << endl << endl;

}


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
		cout << "請依序輸入"<<i<<"號玩家名稱: ";
		cin >> name;
		p[i].setName(name);
	}

	cout << endl << "==== 遊戲開始 ====" << endl;
	cout << "地圖總共有 " << myMap.getSize() << " 格" << endl;
	cout << "玩家 " << p[1].getName() << " 準備出發！" << endl;
	cout << endl << endl;


	// 2. 模擬進行 3 回合的遊戲
	for (int turn = 1; turn <= 6; turn++) {
		Sleep(500);
		cout << "[第 " << turn << " 回合]" << endl;

		for (int i = 1; i <= players; i++) {
			cout << "輪到玩家 " << p[i].getName() << endl;

			if (p[i].getPrison() > 0) {
				cout << "坐牢休息一次" << endl;
				p[i].setPrison(p[i].getPrison()-1);
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
			cout << p[i].getName() << " 擲出了 " << steps << " 點。" << endl<<endl;

			drawMap(myMap, p, players);

			if (p[i].getPosition() + steps > myMap.getSize()) {
				p[i].addMoney(1000);
				cout << " -> 新的一圈，獲得 1000 元！目前金額: " << p[i].getMoney() << " 元" << endl;
			}

			// 步驟 B: 計算新位置
			int currentPos = p[i].getPosition();
			int newPos = (currentPos + steps) % myMap.getSize();

			// 步驟 C: 更新玩家位置
			p[i].setPosition(newPos);

			// 步驟 D: 從地圖上取得玩家踩到的「那一格」資料
			Cell& landedCell = myMap.getCell(newPos);

			// 步驟 E: 印出結果
			cout << p[i].getName() << " 移動到了第 " << newPos << " 格: [" << landedCell.getName() << "]" << endl;

			// 簡單判斷一下踩到了什麼
			if (landedCell.getType() == CellType::Start) {
				cout << " -> 踩到起點！休息一下" << endl;
			}
			else if (landedCell.getType() == CellType::Land) {
				char choice;
				if (landedCell.getOwner() == -1) {
					cout << " -> 這塊土地目前沒有人擁有，價格是: " << landedCell.getPrice() << " 元" << endl;
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
				else if(landedCell.getOwner()!=i){
					cout << "你踩到 "<< p[landedCell.getOwner()].getName()<<" 的土地了！需要支付過路費: " << landedCell.getToll() << " 元" << endl;
					p[i].payMoney(landedCell.getToll());
					p[landedCell.getOwner()].addMoney(landedCell.getToll());
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

	cout << "==== 遊戲結束 ====" << endl;
	
	for (int i = 1; i <= players; i++) {
		cout << "玩家 " << p[i].getName() << " 最終金額: " << p[i].getMoney() << " 元" << endl;
		p[i].printOwnedLands(myMap);
	}

}