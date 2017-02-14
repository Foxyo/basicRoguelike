#include <iostream>
#include <cstdlib>
#include "Generator.h"
#include "monsters.h"

typedef struct player
{
    int xPos;
    int yPos;
    int health = 30;
    int defence = 1;
    int attackDamage = 3;

} player;


void handlePlayerInput(player& newPlayer, char& lastTile, Generator& test, newMonster monsterList[16]);
void printRoomsParameters(Generator& test);
void printRoomEdges(Generator& test);
void monstersInfoPrint(newMonster monsterList[16], Generator& test);
void displayPlayerInfo(player& newPlayer);
void handleMonsterActions(newMonster monsterList[16], Generator& test, player& newPlayer);
void monstersBehOneInfo(newMonster monsterList[16], Generator& test);
void checkIfDead(int ID, newMonster monsterList[16], Generator& test);
void attackMonster(int ID, newMonster monsterList[16], int damage);
int findMonsterID(int x, int y, newMonster monsterList[16]);
int isMonster(int x, int y, Generator& test);
