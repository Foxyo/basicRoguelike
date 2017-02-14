#include <iostream>
#include <cstdlib>
#include "items.h"
#include "Generator.h"
#include "monsters.h"
#ifndef LISELLOCH_MAINFUNCTS_H
#define LISELLOCH_MAINFUNCTS_H


typedef struct player
{
    int xPos;
    int yPos;
    int health = 30;
    int defence = 1;
    int attackDamage = 3;
    int experience = 0;
    int itemsOnPlayer = 0;
    int armourDefence;
    int weaponDamage;
    int regeneration;
    int additionalHealth;
    int isWearingRings = 0;
    int isWieldingWeapon = 0;
    int hasArmour = 0;
    int carriesNecklace = 0;
    int level = 0;
} player;

void handleLevelUps(player& newPlayer);
void handlePlayerInput(player& newPlayer, char& lastTile, Generator& test, newMonster monsterList[16], newItem playerBackpack[30], newItem itemList[500], newItem placedItems[200], int& placedItemsTotal);
void printRoomsParameters(Generator& test);
void printRoomEdges(Generator& test);
void monstersInfoPrint(newMonster monsterList[16], Generator& test);
void displayPlayerInfo(player& newPlayer);
void handleMonsterActions(newMonster monsterList[16], Generator& test, player& newPlayer);
void monstersBehOneInfo(newMonster monsterList[16], Generator& test);
void checkIfDead(int ID, newMonster monsterList[16], Generator& test, player& newPlayer);
void attackMonster(int ID, newMonster monsterList[16], int damage);
int findMonsterID(int x, int y, newMonster monsterList[16]);
int isMonster(int x, int y, Generator& test);
int isPlayer(int x, int y, Generator& test);
int findPlacedItemIndex(int x, int y, Generator& test, newItem placedItems[200]);
int isItem(Generator& test, int x, int y);
void takeItem(Generator& test, int x, int y, newItem placedItems[200], int IID);
void printPlayerBackpack(newItem playerBackpack[30], player newPlayer);
void handlePlayerStatus(player& newPlayer, newItem playerBackpack[30]);
int findLowerUnoccupiedBPIndex(newItem playerBackpack[30]);
#endif // LISELLOCH_MAINFUNCTS_H
