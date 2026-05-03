#ifndef CELLTYPES_H
#define CELLTYPES_H
#include "Cell.h"
#include <string>
using std::string;

class Player;
class Map;
class CardManager;
class BankruptcyManager;

class StartCell : public Cell {
public:
	StartCell(string n);
	void triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) override;
};

class LandCell : public Cell {
public:
	// 繼承父類別的建構子 (寫法你可以自己嘗試一下)
	LandCell(string n, int p, int to, int sell, int h);

	// 覆寫觸發事件！
	void triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) override;

};

class ChanceCell : public Cell {
public:
	ChanceCell(string n);
	void triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) override;
};

class FateCell : public Cell {
public:
	FateCell(string n);
	void triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) override;
};

class JailCell : public Cell {
public:
	JailCell(string n);

	void triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) override;

};

class PublicLandCell : public Cell {
public:
	PublicLandCell(string n);
	void triggerEvent(Player p[], int i, Map& myMap, CardManager& cardAdmin, int players, int loopCurrentPos) override;
};

#endif