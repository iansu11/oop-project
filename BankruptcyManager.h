#ifndef BANKRUPTCYMANAGER_H
#define BANKRUPTCYMANAGER_H
#include "Player.h"
#include "Map.h"

class BankruptcyManager {
public:
	static void checkBankruptcy(Player& currentPlayer, Map& myMap);

};

#endif