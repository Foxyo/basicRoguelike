#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "Generator.h"
#include "mainFuncts.h"
#include "monsters.h"
#include "items.h"
#include <thread>
#include <chrono>


using namespace std;

int victoryCondition = rand()%2+1;

int main()
{
    player newPlayer;
    Generator test;
    newMonster monsterList[16];
    newItem itemList[501];
    newItem placedItems[200];
    newItem playerBackpack[30];
    itemArray(itemList);
    //printItemProperties(itemList);

    char lastTile = test.Map[test.ladderxPos[0]][test.ladderyPos[0]];
    newPlayer.xPos = test.ladderxPos[0];
    newPlayer.yPos = test.ladderyPos[0];
    int turns = 0;
    int levelsGenerated = 0;
    //printRoomEdges(test);
    //printRoomsParameters(test);
    createMonster(monsterList);
    placeMonsters(test, lastTile, monsterList);
    //monstersBehOneInfo(monsterList, test);
    int placedItemsTotal = placeItemsInRooms(itemList, test, placedItems);
    //printPlacedItemsInfo(placedItems, placedItemsTotal);
    printPlacedItems(placedItems, test, placedItemsTotal);
    //test.addSpecialItem(test.ladderxPos, test.ladderyPos);
    //monstersInfoPrint(monsterList, test);
    //test.logicMapDraw();
    test.mapDraw();

    while(newPlayer.health > 0)
    {
        handleLevelUps(newPlayer);
        handlePlayerInput(newPlayer, lastTile, test, monsterList, playerBackpack, itemList, placedItems, placedItemsTotal, levelsGenerated);
        handlePlayerStatus(newPlayer, playerBackpack);

        if(turns > 0)
        handleMonsterActions(monsterList, test, newPlayer);
        //monstersBehOneInfo(monsterList, test);
        //monstersInfoPrint(monsterList, test);
        test.mapDraw();
        printPlacedItems(placedItems, test, placedItemsTotal);
        displayPlayerInfo(newPlayer);
        cout << "Dungeon depth: "<< levelsGenerated;
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


