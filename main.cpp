#include <iostream>
#include <vector>
#include "Player.h"
#include "Dice.h"
#include "Cell.h"
#include "Map.h"
using namespace std;

int main() {
	
	// 1. 準備遊戲物件
	Map myMap;                     // 建立地圖 (會自動呼叫建構子把 6 個格子塞進去)
	Player p1("Alice", 1500);      // 建立玩家 Alice，初始資金 1500
	Dice dice;                     // 建立一顆骰子

	cout << "=== 遊戲開始 ===" << endl;
	cout << "玩家 " << p1.getName() << " 準備出發！" << endl;
	cout << "地圖總共有 " << myMap.getSize() << " 格" << endl;
	cout << "------------------" << endl;

	// 2. 模擬進行 3 回合的遊戲
	for (int turn = 1; turn <= 3; turn++) {
		cout << "[第 " << turn << " 回合]" << endl;

		// 步驟 A: 擲骰子
		int steps = dice.getNumber();
		cout << p1.getName() << " 擲出了 " << steps << " 點。" << endl;

		// 步驟 B: 計算新位置
		// 【老師的數學小教室】利用餘數 (%) 來達成「繞地圖一圈」的效果
		// 假設目前在第 4 格，擲出 3 點，4+3=7。但地圖只有 6 格(0~5)。
		// 7 % 6 = 1，所以玩家會精準地走到第 1 格！
		int currentPos = p1.getPosition();
		int newPos = (currentPos + steps) % myMap.getSize();

		// 步驟 C: 更新玩家位置
		p1.setPosition(newPos);

		// 步驟 D: 從地圖上取得玩家踩到的「那一格」資料
		Cell& landedCell = myMap.getCell(newPos);

		// 步驟 E: 印出結果
		cout << p1.getName() << " 移動到了第 " << newPos << " 格: [" << landedCell.getName() << "]" << endl;

		// 簡單判斷一下踩到了什麼
		if (landedCell.getType() == CellType::Start) {
			cout << " -> 踩到起點啦！" << endl;
		}
		else if (landedCell.getType() == CellType::Land) {
			cout << " -> 這是一塊土地，價格是: " << landedCell.getPrice() << " 元" << endl;
		}
		else if (landedCell.getType() == CellType::Jail) {
			cout << " -> 糟糕！踩到監獄了！" << endl;
		}

		cout << "------------------" << endl;
	}


	/*Player p1("Alice", 1500);
	cout << p1.getName() << endl;
	cout << p1.getMoney() << endl;
	cout << p1.getPosition() << endl;

	p1.addMoney(200);
	p1.payMoney(1000);
	p1.buyLand(12);

	cout << "購買後金額: " << p1.getMoney() << endl;
	p1.sellLand(12, 800);
	cout << "賣出後金額: " << p1.getMoney() << endl;*/

}