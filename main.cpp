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
#include <time.h>

using namespace std;



int main()
{
    srand(time(NULL));
    int gameDepth = rand()%10+3;
    //int gameDepth = 1;
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
    createMonster(monsterList, levelsGenerated);
    placeMonsters(test, lastTile, monsterList);
    //monstersBehOneInfo(monsterList, test);
    int placedItemsTotal = placeItemsInRooms(itemList, test, placedItems);
    //printPlacedItemsInfo(placedItems, placedItemsTotal);
    printPlacedItems(placedItems, test, placedItemsTotal);
    //test.addSpecialItem(test.ladderxPos, test.ladderyPos);
    //monstersInfoPrint(monsterList, test);
    //test.logicMapDraw();
    system("clear");
    cout << "You've got no idea why you'd let that old crook make you visit this forsaken place." << endl;
    this_thread::sleep_for(chrono::milliseconds(700));
    cout << "Perhaps it was the need of these shiny gold pieces that convinced you...?" << endl;
    this_thread::sleep_for(chrono::milliseconds(700));
    cout << "Anyway..." << endl;
    this_thread::sleep_for(chrono::milliseconds(700));
    cout << "From what you've been told, this hell 'o a hole has multiple levels." << endl;
    this_thread::sleep_for(chrono::milliseconds(700));
    cout << "..." << gameDepth << " to be exact." << endl;
    this_thread::sleep_for(chrono::milliseconds(700));
    cout << "...and it ain't particularly safe there either. With goblins, trolls, spiders..." << endl;
    cout << "You gulp silently, as you descend to the lair and the sunlight starts to fade." << endl;
    this_thread::sleep_for(chrono::milliseconds(700));
    cout << "Press any key to continue..." << endl;
    system("stty raw");
    char temp = getchar();
    system("stty cooked");

    int isSet = 0;
    int wonOrLost;

    //test.mapDraw();

    while(1)
    {
        cout << "\033[2J\033[1;1H";
        //system("clear");
        //cout << "pxPos pyPos lxPos lyPos"  << newPlayer.xPos << " " << newPlayer.yPos << " " << test.ladderxPos[1] << " " << test.ladderyPos[1] << endl;
        if(newPlayer.xPos == test.ladderxPos[1] && test.ladderyPos[1] == newPlayer.yPos && lastTile == '*')
        {
            wonOrLost = 1;
            break;
        }
        if(newPlayer.health <= 0)
        {
            wonOrLost = 0;
            break;
        }
        if(levelsGenerated == gameDepth && isSet!=1)
        {
            test.addSpecialItem(test.ladderxPos, test.ladderyPos);
            isSet = 1;
        }

        //placement1
        test.mapDraw();
        printPlacedItems(placedItems, test, placedItemsTotal);
        displayPlayerInfo(newPlayer);


        handleLevelUps(newPlayer);
        handlePlayerInput(newPlayer, lastTile, test, monsterList, playerBackpack, itemList, placedItems, placedItemsTotal, levelsGenerated);
        handlePlayerStatus(newPlayer, playerBackpack);

        if(turns > 0)
            handleMonsterActions(monsterList, test, newPlayer);
        //monstersBehOneInfo(monsterList, test);
        //monstersInfoPrint(monsterList, test);

        //cout << "\033[2J\033[1;1H";
        //placement2
        //test.mapDraw();
        //printPlacedItems(placedItems, test, placedItemsTotal);
        //displayPlayerInfo(newPlayer);

        //cout << "Dungeon depth: "<< levelsGenerated;
        //test.logicMapDraw();
        turns++;
        this_thread::sleep_for(chrono::milliseconds(10));
        system("clear");

        // printRoomEdges(test);
        //printRoomsParameters(test);

        // cout<<lastTile << " " << turns;
    }
    wonOrLostMsg(wonOrLost, newPlayer);
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


