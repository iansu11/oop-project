#include "GameRules.h"
#include <iostream>
#include <conio.h> // 用於 _getch() 函數
#include "BankruptcyManager.h"
#include "Map.h"
using namespace std;

bool RuleManager::jailRule(Player& p, CardManager& cardAdmin) {
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
					return false;
				}
				else if (choice == 'n' || choice == 'N') {
					cout << "選擇不使用免坐牢卡，這回合照常坐牢。" << endl;
					cout << "坐牢休息一次" << endl;
					p.setPrison(p.getPrison() - 1);
					cout << "------------------" << endl;
					return true;
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
			return true;
		}
	}
	return false;
}

void RuleManager::selectGameMode(int& gameMode, int& maxTurns, int& targetAmount) {
	cout << "請選擇遊戲模式：" << endl;
	cout << "1. 回合制 | 2. 目標制 | 3. 破產制 : ";

	while (true) {
		string input; // 每次迴圈重新接收
		cin >> input;

		// 防呆：長度必須為 1，且在 '1' 到 '3' 之間
		if (input.length() == 1 && input[0] >= '1' && input[0] <= '3') {
			gameMode = input[0] - '0'; // 成功轉換
			cout << "已選擇模式 " << gameMode;
			if (gameMode == 1) {
				cout << ".回合制，請輸入想進行的回合:";
				while (!(cin >> maxTurns)) {
					cin.clear(); // 清除 cin 的錯誤狀態 (Failbit)
					cin.ignore(10000, '\n');//  忽略緩衝區內剩餘的字元，直到遇到換行符號 (\n) 為止
					cout << "輸入無效！請輸入純數字的回合數: ";
				}
			}
			else if (gameMode == 2) {
				int initialMoney = 5000;
				cout << ".目標制，請輸入達成勝利的目標金額 (必須大於初始金額 " << initialMoney << " 元): ";
				while (true) {
					if (!(cin >> targetAmount)) {
						cin.clear(); // 清除 cin 的錯誤狀態 (Failbit)
						cin.ignore(10000, '\n');//  忽略緩衝區內剩餘的字元，直到遇到換行符號 (\n) 為止
						cout << "輸入無效！請輸入純數字的目標金額: ";
					}
					else if (targetAmount <= initialMoney) {
						cout << "[警告] 目標金額太低了！請輸入大於 " << initialMoney << " 的金額: ";
					}
					else {
						break;
					}
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
}

void RuleManager::executeCellAction(Player p[], int i, Map& myMap, int players, CardManager& cardAdmin) {
	while (true) {
		// 每次進迴圈，都要去抓玩家「當下最新的位置」
		int loopCurrentPos = p[i].getPosition();

		// loopCurrentPos 去地圖上抓玩家踩到的「那一格」資料
		Cell* landedCell = myMap.getCell(loopCurrentPos);

		// 印出結果
		cout << p[i].getName() << " 移動到了第 " << loopCurrentPos << " 格: [" << landedCell->getName() << "]" << endl << endl;

		myMap.drawMap(p, players);

		landedCell->triggerEvent(p, i, myMap, cardAdmin, players, loopCurrentPos);

		if (p[i].getPosition() != loopCurrentPos) {
			continue; // 重新判定新格子！
		}
		
		break;
	}
}

void RuleManager::announceWinner(int gameMode, Player p[], int players, Map& myMap, int winnerIndex) {
	if (gameMode == 1) {
		int maxAssets = -9999;
		int maxOwner = 1, tieCount = 0;
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

			return;
		}
		else {
			cout << "本局遊戲出現平手，以下玩家並列獲勝！" << endl;
			for (int i = 1;i <= players;i++) {
				if (asset[i] == maxAssets) {
					cout << "玩家 " << p[i].getName() << " 獲得最終勝利！" << endl;
					cout << "總資產為: " << maxAssets << " 元" << endl;
				}
			}
			return;
		}
	}

	else if (gameMode == 2 || gameMode == 3) {

		cout << "恭喜玩家 " << p[winnerIndex].getName() << " 獲得最終勝利！" << endl;
		cout << "總資產為: " << p[winnerIndex].getTotalAssets(myMap) << " 元" << endl;

		return;
	}
}
