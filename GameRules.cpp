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

void selectGameMode(int& gameMode, int& maxTurns, int& targetAmount) {
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

void announceWinner(int gameMode, Player p[], int players, Map& myMap, int winnerIndex) {
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
