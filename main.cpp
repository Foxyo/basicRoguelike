#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "Generator.h"
#include "mainFuncts.h"
#include "monsters.h"
#include <thread>
#include <chrono>


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
    //printRoomEdges(test);
    //printRoomsParameters(test);
    createMonster(monsterList);
    placeMonsters(test, lastTile, monsterList);
    monstersBehOneInfo(monsterList, test);
    //monstersInfoPrint(monsterList, test);
    //test.logicMapDraw();
    test.mapDraw();

    while(1)
    {
        handlePlayerInput(newPlayer, lastTile, test, monsterList);
        if(turns > 0)
        handleMonsterActions(monsterList, test, newPlayer);
        //monstersBehOneInfo(monsterList, test);
        //monstersInfoPrint(monsterList, test);
        test.mapDraw();
        displayPlayerInfo(newPlayer);
        //test.logicMapDraw();
        turns++;
        this_thread::sleep_for(chrono::milliseconds(10));

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


