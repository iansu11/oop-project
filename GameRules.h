#ifndef GAMERULES_H
#define GAMERULES_H
#include "Player.h"
#include "CardManager.h"

void jailRule(Player& p, CardManager& cardAdmin,bool& skip);

void executeCellAction(Player p[], int i, Map& myMap, int players, CardManager& cardAdmin);

#endif
