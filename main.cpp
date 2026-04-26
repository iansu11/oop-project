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
#include "CardManager.h"
#include "BankruptcyManager.h"
#include "GameRules.h"
using namespace std;

int main() {
	srand(time(0));

	Map myMap;                    
	Player p[5];
	Dice dice;  
	CardManager cardAdmin;
	int players=0, gameMode=0;


	cout << "請輸入玩家人數 (2-4): ";

	
	while (true) {
		char number= _getch();

		if (number >= '2' && number <= '4') {
			players = number - '0'; // 將字符轉換為整數
			cout << players << endl;
			break;
		}
		else {
			cout << endl << "玩家人數必須在 2 到 4 之間，請重新輸入: ";
		}

	}



	for (int i = 1;i <= players;i++) {
		string name;
		cout << endl << "請依序輸入"<<i<<"號玩家名稱(P"<<i<<"):";
		cin >> name;
		p[i].setName(name);
	}

	/*
	cout << "請選擇遊戲模式：" << endl;
	cout << "1. 回合制 (設定回合數，結束時資產最高者獲勝)" << endl;
	cout << "2. 目標制 (設定目標金額，先達到者獲勝)" << endl;
	cout << "3. 破產制 (傳統玩法，活到最後的玩家獲勝)" << endl;

	while (true) {
		char number = _getch();

		if (number >= '1' && number <= '3') {

			gameMode = number - '0'; // 將字符轉換為整數
			cout << gameMode << endl;
			break;
		}
		else {
			cout << endl << "玩家人數必須在 1 到 4 之間，請重新輸入: ";
		}

	}
	*/

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

			//---坐牢判定開始---
			bool skip = false;

			jailRule(p[i], cardAdmin, skip);

			if (skip == true) {
				continue; 
			}
			//---坐牢判定結束---

			if(p[i].getBankruptcy()==1){
				cout << "已經破產了，換下一位玩家" << endl;
				cout << "------------------" << endl;
				continue;
			}

			// 擲骰子
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

			// 計算玩家新位置
			int currentPos = p[i].getPosition();
			int newPos = (currentPos + steps) % myMap.getSize();

			// 更新玩家位置
			p[i].setPosition(newPos);

			// 進行格子判斷
			executeCellAction(p, i, myMap, players, cardAdmin);

			cout << "------------------" << endl;
		}
		cout << endl;
	}

	cout << "==== 遊戲結束 ====" << endl<<endl;
	
	for (int i = 1; i <= players; i++) {
		cout << "玩家 " << p[i].getName() << " 最終金額: " << p[i].getMoney() << " 元" << endl;
		p[i].printOwnedLands(myMap);
		cout << "總資產: " << p[i].getTotalAssets(myMap) << " 元" << endl;
		cout << endl;
	}

	int maxAssets = p[1].getTotalAssets(myMap);
	int maxOwner = 1;

	for (int i = 2; i <= players; i++) {
		if (p[i].getTotalAssets(myMap) > maxAssets) {
			maxAssets = p[i].getTotalAssets(myMap);
			maxOwner = i;
		}
	}

	cout << "恭喜玩家 " << p[maxOwner].getName() << " 獲得最終勝利！" << endl;
	cout << "總資產為: " << maxAssets << " 元" << endl;
}