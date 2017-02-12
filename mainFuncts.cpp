#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "mainFuncts.h"

void handlePlayerInput(player& newPlayer, char& lastTile, Generator& test)
{
    system("stty raw");
    char input = getchar();
    system("stty cooked");

    //cout<<lastTile<<endl;
    //cout<<test.Map[newPlayer.xPos][newPlayer.yPos]<<endl;
    test.Map[newPlayer.xPos][newPlayer.yPos] = lastTile;

    switch(input)
    {
    case 'w':
    {
        newPlayer.yPos = newPlayer.yPos -1;
        if(test.isLegitMove(newPlayer.xPos, newPlayer.yPos) == 0)
            newPlayer.yPos = newPlayer.yPos +1;
        break;
    }
    case 'd':
    {
        newPlayer.xPos = newPlayer.xPos +1;
        if(test.isLegitMove(newPlayer.xPos, newPlayer.yPos) == 0)
            newPlayer.xPos = newPlayer.xPos -1;
        break;
    }
    case 's':
    {
        newPlayer.yPos = newPlayer.yPos +1;
        if(test.isLegitMove(newPlayer.xPos, newPlayer.yPos) == 0)
            newPlayer.yPos = newPlayer.yPos -1;
        break;
    }
    case 'a':
    {
        newPlayer.xPos = newPlayer.xPos -1;
        if(test.isLegitMove(newPlayer.xPos, newPlayer.yPos) == 0)
            newPlayer.xPos = newPlayer.xPos +1;
        break;
    }
    case 'q':
    {
        exit(0);
    }
    case 'e':
    {
        if(lastTile == 'H' && test.logicMap[newPlayer.xPos][newPlayer.yPos] != '0')
        {
            test.Generate();
            test.mapDraw();
            newPlayer.xPos = test.ladderxPos[0];
            newPlayer.yPos = test.ladderyPos[0];
            lastTile = test.Map[test.ladderxPos[0]][test.ladderyPos[0]];
        }
        break;
    }


    }
    lastTile = test.Map[newPlayer.xPos][newPlayer.yPos];
    test.Map[newPlayer.xPos][newPlayer.yPos] = '@';
}

void printRoomEdges(Generator& test)
{
    for(int i = 0; i < test.endRoomCount; i++)
    {
        cout << i << "Room fEgdeX" << " " << test.fRoomEdgesX[i] << endl;
        cout << i << "Room fEgdeY" << " " << test.fRoomEdgesY[i] << endl;
        cout << "remembered val: " << test.Map[test.fRoomEdgesX[i]][test.fRoomEdgesX[i]] << endl;
        cout << i << "Room lEgdeX" << " " << test.lRoomEdgesX[i] << endl;
        cout << i << "Room lEgdeY" << " " << test.lRoomEdgesY[i] << endl;
        cout << "remembered val: " << test.Map[test.lRoomEdgesX[i]][test.lRoomEdgesX[i]] << endl;
    }
}

void printRoomsParameters(Generator& test)
{
    for(int i = 0; i < test.endRoomCount; i++)
    {
        cout << i << "Room Width" << test.roomWidth[i] << endl;
        cout << i << "Room Height" << test.roomHeight[i] << endl;
    }
}
void monstersInfoPrint(newMonster monsterList[16], Generator& test)
{
    for(int i = 0; i<16; i++)
    {
        cout << "Symbol " << monsterList[i].symbol << endl;
        cout << "health " << monsterList[i].health << endl;
        cout << "armour" << monsterList[i].armour << endl;
        cout << "attackDamage " << monsterList[i].attackDamage << endl;
        cout << "behaviourType " << monsterList[i].behaviourType << endl;
        cout << "xPos " << monsterList[i].xPos << endl;
        cout << "yPos " << monsterList[i].yPos << endl;
        cout << "xPosInit " << monsterList[i].xPosInit << endl;
        cout << "yPosInit " << monsterList[i].yPosInit << endl;
        cout << "map xPos yPos val " << "/" <<test.Map[monsterList[i].xPos][monsterList[i].yPos] << "/" << endl;
        cout << "ID" << monsterList[i].ID << endl;
        cout << "PlacedCorrectly" << monsterList[i].placedCorrectly << endl;
        cout << endl;
    }
}


