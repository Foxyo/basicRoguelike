#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "Generator.h"

#ifndef LISELLOCH_MONSTERS_H
#define LISELLOCH_MONSTERS_H

struct newMonster
{
    char symbol;
    int health;
    int armour;
    int attackDamage;
    int behaviourType;
    int xPos;
    int yPos;
    int ID;
    int placedCorrectly;
    int xPosInit;
    int yPosInit;
    char lastTile;
    char dominantTile;
    int gaveExp = 0;
};


void createMonster(newMonster monsterList[16], int& levelsGenerated);
newMonster selectMonster(int& levelsGenerated);
void placeMonsters(Generator &test, char &lastTile, newMonster monsterList[16]);


#endif // LISELLOCH_MONSTERS_H
