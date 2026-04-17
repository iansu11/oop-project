#ifndef CARDMANAGER_H
#define CARDMANAGER_H
#include "Player.h"
#include "Map.h"
#include <string>
#include <vector>

class CardManager{
private:
    std::vector<int> chanceDeck;
    std::vector<int> fateDeck;
public:
	CardManager();

    void returnFreeJailCard();

    void executeChance(Player& currentPlayer, Map& gameMap, Player p[], int playerCount);
    void executeFate(Player& currentPlayer, Map& gameMap, Player p[], int playerCount);
};

#endif