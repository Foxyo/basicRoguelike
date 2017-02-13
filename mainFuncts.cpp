#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "mainFuncts.h"

void handlePlayerInput(player& newPlayer, char& lastTile, Generator& test, newMonster monsterList[16])
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
            newPlayer.xPos = test.ladderxPos[0];
            newPlayer.yPos = test.ladderyPos[0];
            lastTile = test.Map[test.ladderxPos[0]][test.ladderyPos[0]];
            createMonster(monsterList);
            placeMonsters(test, lastTile, monsterList);
            test.mapDraw();
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
        cout << "lastTile " << monsterList[i].lastTile << endl;
        cout << endl;
    }
}

void monstersBehOneInfo(newMonster monsterList[16], Generator& test)
{
    for(int i = 0; i < 16; i++)
    {
        if(monsterList[i].behaviourType == 1)
        {
            cout << "ID" << monsterList[i].ID << endl;
            cout << "xPos " << monsterList[i].xPos << endl;
            cout << "yPos " << monsterList[i].yPos << endl;
            cout << "lastTile " << monsterList[i].lastTile << endl;
            cout << "Map tile: " << test.Map[monsterList[i].xPos][monsterList[i].yPos];
            cout << endl;
        }
    }

}

void displayPlayerInfo(player& newPlayer)
{
    cout << "Health: " << newPlayer.health << "    " << "Armor: " << newPlayer.defence << "    " << "Dmg: " << newPlayer.attackDamage;
}

void handleMonsterActions(newMonster monsterList[16], Generator& test, player& newPlayer)
{
    for(int i = 0; i < 16; i++)
    {
        if(monsterList[i].behaviourType == 1 && monsterList[i].placedCorrectly == 1)
        {

            int monsterMove = rand()%4 + 1;

            test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].lastTile;

            switch(monsterMove)
            {
            case 1:
            {
                if(test.isLegitMoveMonster(monsterList[i].xPos + 1, monsterList[i].yPos) == 1)
                {
                    monsterList[i].xPos++;
                }
                break;
            }

            case 2:
            {
                if(test.isLegitMoveMonster(monsterList[i].xPos - 1, monsterList[i].yPos) == 1)
                {
                    monsterList[i].xPos--;
                }
                break;
            }

            case 3:
            {
                if(test.isLegitMoveMonster(monsterList[i].xPos, monsterList[i].yPos + 1) == 1)
                 {
                    monsterList[i].yPos++;
                }
                break;
            }

            case 4:
            {
                if(test.isLegitMoveMonster(monsterList[i].xPos, monsterList[i].yPos - 1) == 1)
                {
                    monsterList[i].yPos--;
                }
                break;
            }

            }

            monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
            test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;

        }
            if(monsterList[i].behaviourType == 2 && monsterList[i].placedCorrectly == 1)
            {
                if(abs((monsterList[i].xPos-1) - newPlayer.xPos) < abs(monsterList[i].xPos - newPlayer.xPos) && (test.Map[monsterList[i].xPos -1][monsterList[i].yPos] == '.' || test.Map[monsterList[i].xPos -1][monsterList[i].yPos] == '+'))
                {
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].lastTile;
                    monsterList[i].xPos--;
                    monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;
                }
                if(abs((monsterList[i].xPos+1) - newPlayer.xPos) < abs(monsterList[i].xPos - newPlayer.xPos) && (test.Map[monsterList[i].xPos +1][monsterList[i].yPos] == '.' || test.Map[monsterList[i].xPos +1][monsterList[i].yPos] == '+'))
                {
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].lastTile;
                    monsterList[i].xPos++;
                    monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;
                }
                if(abs((monsterList[i].yPos+1) - newPlayer.yPos) < abs(monsterList[i].yPos - newPlayer.yPos) && (test.Map[monsterList[i].xPos][monsterList[i].yPos + 1] == '.' || test.Map[monsterList[i].xPos][monsterList[i].yPos +1] == '+'))
                {
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].lastTile;
                    monsterList[i].yPos++;
                    monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;
                }
                if(abs((monsterList[i].yPos-1) - newPlayer.yPos) < abs(monsterList[i].yPos - newPlayer.yPos) && (test.Map[monsterList[i].xPos][monsterList[i].yPos - 1] == '.' || test.Map[monsterList[i].xPos][monsterList[i].yPos -1] == '+'))
                {
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].lastTile;
                    monsterList[i].yPos--;
                    monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;
                }
                else;

            }
    }


}


