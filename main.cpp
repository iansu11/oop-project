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
		string number; // 每次迴圈重新接收
		cin >> number;

		if (number.length() == 1 && number[0] >= '2' && number[0] <= '4') {
			players = number[0] - '0'; // 將字符轉換為整數
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
	cout << endl;
	
	int targetAmount = 0;   // 用來存玩家設定的目標金額
	bool isGameOver = false;// 遊戲結束的開關 (取代原本寫死的 15 回合)
	int currentTurn = 1;    // 現在是第幾回合
	int winnerIndex = -1;   // 用來記錄最後是幾號玩家贏了
	int maxTurns = 0;      // 用來存玩家設定的最大回合數

	cout << "請選擇遊戲模式：" << endl;
	cout << "1. 回合制 | 2. 目標制 | 3. 破產制 : ";

	while (true) {
		string input; // 每次迴圈重新接收
		cin >> input;

		// 防呆：長度必須為 1，且在 '1' 到 '3' 之間
		if (input.length() == 1 && input[0] >= '1' && input[0] <= '3') {
			gameMode = input[0] - '0'; // 成功轉換
			cout << "已選擇模式 " << gameMode ;
			if (gameMode == 1) {
				cout << ".回合制，請輸入想進行的回合:";
				while (!(cin >> maxTurns)) {
					cin.clear(); // 清除 cin 的錯誤狀態 (Failbit)
					cin.ignore(10000,'\n');//  忽略緩衝區內剩餘的字元，直到遇到換行符號 (\n) 為止
					cout << "輸入無效！請輸入純數字的回合數: ";
				}
			}
			else if (gameMode == 2) {
				cout << ".目標制，請輸入達成勝利的目標金額:";
				while (!(cin >> targetAmount)) {
					cin.clear(); // 清除 cin 的錯誤狀態 (Failbit)
					cin.ignore(10000,'\n');//  忽略緩衝區內剩餘的字元，直到遇到換行符號 (\n) 為止
					cout << "輸入無效！請輸入純數字的目標金額: ";
				}
			}
			else if (gameMode == 3) {
				cout << ".破產制，遊戲將持續進行直到只剩下一位玩家未破產。" << endl;
			}
			break; // 跳出無限迴圈
		}
		else {
			cout << "[錯誤] 請輸入正確的數字 (1-3) :" << endl;
		}
	}
	

	cout << endl << "==== 遊戲開始 ====" << endl;
	cout << "地圖總共有 " << myMap.getSize() << " 格" << endl;
	cout << "玩家 " << p[1].getName() << " 準備出發！" << endl;
	cout << endl << endl;


	// 回合開始
	while (!isGameOver) {
		Sleep(500);
		cout << "[第 " << currentTurn << " 回合]" << endl;

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

			int activePlayers = 0;
			int potentialWinner = -1;
			for (int j = 1; j <= players; j++) {
				if (!p[j].getBankruptcy()) {
					activePlayers++;
					potentialWinner = j;
				}
			}

			if (activePlayers == 1) {
				isGameOver = true;
				winnerIndex = potentialWinner;
				break;
			}

			if (gameMode == 2) {
				if (p[i].getTotalAssets(myMap) >= targetAmount) {
					isGameOver = true;
					winnerIndex = i;
					break;
				}
				
			}
			
			cout << "------------------" << endl;
		}
		cout << endl;

		if (isGameOver) {
			break; 
		}

		if (gameMode == 1 && currentTurn >= maxTurns) {
			isGameOver = true;
		}
		
		currentTurn++;
	}

	cout << "==== 遊戲結束 ====" << endl<<endl;
	
	for (int i = 1; i <= players; i++) {
		cout << "玩家 " << p[i].getName() << " 最終金額: " << p[i].getMoney() << " 元" << endl;
		p[i].printOwnedLands(myMap);
		cout << "總資產: " << p[i].getTotalAssets(myMap) << " 元" << endl;
		cout << endl;
	}

	if (gameMode == 1) {
		int maxAssets = -9999;
		int maxOwner = 1,tieCount = 0;
		int asset[5] = {};

		for (int i = 1; i <= players; i++) {
			if (p[i].getBankruptcy() == 0) {
				asset[i] = p[i].getTotalAssets(myMap);

				if (p[i].getTotalAssets(myMap) > maxAssets) {
					maxAssets = p[i].getTotalAssets(myMap);
					maxOwner = i;
					tieCount = 0;
				}
				if (p[i].getTotalAssets(myMap) == maxAssets) {
					tieCount++;
				}
			}	
		}

		if (tieCount == 1) {
			cout << "恭喜玩家 " << p[maxOwner].getName() << " 獲得最終勝利！" << endl;
			cout << "總資產為: " << maxAssets << " 元" << endl;
			
			return 0;
		}
		else {
			cout << "本局遊戲出現平手，以下玩家並列獲勝！" << endl;
			for (int i = 1;i <= players;i++) {
				if (asset[i] == maxAssets) {
					cout << "玩家 " << p[i].getName() << " 獲得最終勝利！" << endl;
					cout << "總資產為: " << maxAssets << " 元" << endl;
				}
			}
			return 0;
		}
	}

	else if (gameMode == 2 || gameMode == 3) {
		
		cout << "恭喜玩家 " << p[winnerIndex].getName() << " 獲得最終勝利！" << endl;
		cout << "總資產為: " << p[winnerIndex].getTotalAssets(myMap) << " 元" << endl;
		
		return 0;
	}
}