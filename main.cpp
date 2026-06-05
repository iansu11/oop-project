#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h> // 用於 _getch() 函數
#include <windows.h> // 使用 Sleep()
#include "Player.h"
#include "Dice.h"
#include "Map.h"
#include "CardManager.h"
#include "GameRules.h"
using namespace std;

int main() {
	srand(time(0));

	Map myMap;                    
	Player p[5];
	Dice dice;  
	CardManager cardAdmin;
	int players=0, gameMode=0;
	RuleManager ruleAdmin;


	cout << "請輸入玩家人數 (2-4): ";

	while (true) {
		string number; // 每次迴圈重新接收
		cin >> number;

		if (number.length() == 1 && number[0] >= '2' && number[0] <= '4') {
			players = number[0] - '0'; // 將字符轉換為整數
			cin.ignore(1000, '\n'); // 清除輸入緩衝區
			break;
		}
		else {
			cout << endl << "玩家人數必須在 2 到 4 之間，請重新輸入: ";
			cin.ignore(1000, '\n'); // 清除輸入緩衝區
		}
		
	}

	for (int i = 1;i <= players;i++) {
		string name;
		cout << endl << "請依序輸入"<<i<<"號玩家名稱(P"<<i<<"):";
		getline(cin, name);
		p[i].setName(name);
	}
	cout << endl;
	
	int targetAmount = 0;   // 用來存玩家設定的目標金額
	bool isGameOver = false;// 遊戲結束的開關
	int currentTurn = 1;    // 現在是第幾回合
	int winnerIndex = -1;   // 用來記錄最後是幾號玩家贏了
	int maxTurns = 0;      // 用來存玩家設定的最大回合數

	// 遊戲模式選擇
	ruleAdmin.selectGameMode(gameMode, maxTurns, targetAmount);

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


			// 坐牢判定 GameRule.cpp
			if (ruleAdmin.jailRule(p[i], cardAdmin) == true) {
				continue; // 坐牢，直接跳過換下一位！
			}
		

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

			// 進行格子判斷 GameRules.cpp
			ruleAdmin.executeCellAction(p, i, myMap, players, cardAdmin);

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

			// 回合制結束遊戲判斷
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

		// 破產制提前結束功能，從第20回合後可以自由選擇是否提前結束遊戲
		if (gameMode == 3 && isGameOver==false && currentTurn >= 20) {
			cout << "========================================" << endl;
			cout << "是否要提前結束並結算？" << endl;
			cout << "(按 [E] 結束 / 按 [Enter] 或其他鍵繼續下一回合)" << endl;

			char input = _getch();
			if (input == 'e' || input == 'E') {
				cout << "\n玩家選擇提前結束遊戲！正在結算最高資產..." << endl;
				gameMode = 1;      // 偽裝成回合制，交給現有的回合制結算去比資產大小
				isGameOver = true;
			}
			cout << endl;
		}

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

	// 判斷並列出最終贏家 GameRules.cpp 
	ruleAdmin.announceWinner(gameMode, p, players, myMap, winnerIndex);

}