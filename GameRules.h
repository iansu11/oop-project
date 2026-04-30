#ifndef GAMERULES_H
#define GAMERULES_H
#include "Player.h"
#include "CardManager.h"
#include "Map.h"

void jailRule(Player& p, CardManager& cardAdmin,bool& skip);

void selectGameMode(int& gameMode, int& maxTurns, int& targetAmount);

void executeCellAction(Player p[], int i, Map& myMap, int players, CardManager& cardAdmin);

void announceWinner(int gameMode, Player p[], int players, Map& myMap, int winnerIndex);

#endif
