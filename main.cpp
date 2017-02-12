#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "Generator.h"
#include "mainFuncts.h"
#include "monsters.h"


using namespace std;

/*typedef struct player
{
    int xPos;
    int yPos;
}player;*/



int main()
{
    player newPlayer;
    Generator test;
    newMonster monsterList[16];

    char lastTile = test.Map[test.ladderxPos[0]][test.ladderyPos[0]];
    newPlayer.xPos = test.ladderxPos[0];
    newPlayer.yPos = test.ladderyPos[0];
    cout<<lastTile;
    int turns = 0;
    printRoomEdges(test);
    printRoomsParameters(test);
    createMonster(monsterList);
    placeMonsters(test, lastTile, monsterList);
    monstersInfoPrint(monsterList, test);
    test.logicMapDraw();
    test.mapDraw();

    while(1)
    {
        handlePlayerInput(newPlayer, lastTile, test);
        test.mapDraw();
        test.logicMapDraw();
        turns++;
        // printRoomEdges(test);
        //printRoomsParameters(test);

        // cout<<lastTile << " " << turns;
    }
    return 0;
}

/* logicMap info:
    0-9 normal
    10 = :
    11 = ;
    12 = <
    13 = =
    14 = >
    15 = ?
    16 = @
    17 = A
    18 = B
    19 = C
    and so on and so far
*/


