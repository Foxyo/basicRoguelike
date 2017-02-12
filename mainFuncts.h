#include <iostream>
#include <cstdlib>
#include "Generator.h"
#include "monsters.h"

typedef struct player
{
    int xPos;
    int yPos;
} player;


void handlePlayerInput(player& newPlayer, char& lastTile, Generator& test);
void printRoomsParameters(Generator& test);
void printRoomEdges(Generator& test);
void monstersInfoPrint(newMonster monsterList[16], Generator& test);
