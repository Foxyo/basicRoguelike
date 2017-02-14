#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "mainFuncts.h"

void handlePlayerInput(player& newPlayer, char& lastTile, Generator& test, newMonster monsterList[16])
{
    system("stty raw");
    char input = getchar();
    system("stty cooked");
    int xD = input;
    cout << "/" << xD << "/" << endl;

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
    case '\x20':
    {
        system("stty raw");
        char input2 = getchar();
        system("stty cooked");
    switch(input2)
    {
    case 'a':
    {
       //cout << "stage1" << endl;
       if(isMonster(newPlayer.xPos-1, newPlayer.yPos, test) == 1)
        {
            //cout << "p xPos p yPos" << newPlayer.xPos << " " << newPlayer.yPos;
            //cout << "stage2" << endl;
            int ID = findMonsterID(newPlayer.xPos-1, newPlayer.yPos, monsterList);
            //cout << "stage3" << endl;
            //cout << "ID: " << ID << endl;
            monstersInfoPrint(monsterList, test);
            //cout << "m xPos m yPos" << monsterList[ID].xPos << " " << monsterList[ID].yPos << endl;
            monsterList[ID].health -= newPlayer.attackDamage;
            monsterList[ID].behaviourType = 2;

            if(monsterList[ID].health < 0)
            {
                //cout << "ayy" << endl;;
                test.Map[newPlayer.xPos-1][newPlayer.yPos] = monsterList[ID].dominantTile;
            }
            //attackMonster(ID, monsterList, newPlayer.attackDamage);

            //checkIfDead(ID, monsterList, test);
        }
        break;
    }
    case 'd':
    {
       if(isMonster(newPlayer.xPos+1, newPlayer.yPos, test) == 1)
        {
            int ID = findMonsterID(newPlayer.xPos+1, newPlayer.yPos, monsterList);
            monstersInfoPrint(monsterList, test);
            monsterList[ID].health -= newPlayer.attackDamage;
            monsterList[ID].behaviourType = 2;
            if(monsterList[ID].health < 0)
            {
                test.Map[newPlayer.xPos+1][newPlayer.yPos] = monsterList[ID].dominantTile;
            }
        }
        break;
    }
    case 'w':
    {
       if(isMonster(newPlayer.xPos, newPlayer.yPos-1, test) == 1)
        {
            int ID = findMonsterID(newPlayer.xPos, newPlayer.yPos-1, monsterList);
            monstersInfoPrint(monsterList, test);
            monsterList[ID].health -= newPlayer.attackDamage;
            monsterList[ID].behaviourType = 2;
            if(monsterList[ID].health < 0)
            {
                test.Map[newPlayer.xPos][newPlayer.yPos-1] = monsterList[ID].dominantTile;
            }
        }
        break;
    }
    case 's':
    {
       if(isMonster(newPlayer.xPos, newPlayer.yPos+1, test) == 1)
        {
            int ID = findMonsterID(newPlayer.xPos, newPlayer.yPos+1, monsterList);
            monstersInfoPrint(monsterList, test);
            monsterList[ID].health -= newPlayer.attackDamage;
            monsterList[ID].behaviourType = 2;
            if(monsterList[ID].health < 0)
            {
                test.Map[newPlayer.xPos][newPlayer.yPos+1] = monsterList[ID].dominantTile;
            }
        }
        break;
    }

    }


    }
    }



    lastTile = test.Map[newPlayer.xPos][newPlayer.yPos];
    test.Map[newPlayer.xPos][newPlayer.yPos] = '@';
}

int isMonster(int x, int y, Generator& test)
{
    if(test.Map[x][y] == 'G' || test.Map[x][y] == 'B' || test.Map[x][y] == 'x' || test.Map[x][y] == 'T')
        return 1;
    else return 0;
}

void checkIfDead(int ID, newMonster monsterList[16], Generator& test)
{
    if(monsterList[ID].health < 0)
    {
        test.Map[monsterList[ID].xPos][monsterList[ID].yPos] = monsterList[ID].lastTile;
    }
}
void attackMonster(int ID, newMonster monsterList[16], int damage)
{
    monsterList[ID].health -= damage;
}

int findMonsterID(int x, int y, newMonster monsterList[16])
{
    cout << "x: y: " << x << " " << y << endl;
    int found = -1;
    int ID;
    for(int i = 0; i < 16; i++)
    {
        cout << "x: y: i:" << x << " " << y << " " << i << endl;
        if(monsterList[i].xPos == x && monsterList[i].yPos == y && found == -1)
        {
            ID = monsterList[i].ID;
            found = 1;

        }

    }
    return ID;

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
        if(monsterList[i].behaviourType == 1 && monsterList[i].placedCorrectly == 1 && monsterList[i].health > 0)
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
            if(test.Map[monsterList[i].xPos][monsterList[i].yPos] == '.' || test.Map[monsterList[i].xPos][monsterList[i].yPos] == '+')
                monsterList[i].dominantTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
            monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
            test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;

        }
            if(monsterList[i].behaviourType == 2 && monsterList[i].placedCorrectly == 1 && monsterList[i].health > 0)
            {
                if(abs((monsterList[i].xPos-1) - newPlayer.xPos) < abs(monsterList[i].xPos - newPlayer.xPos) && (test.Map[monsterList[i].xPos -1][monsterList[i].yPos] == '.' || test.Map[monsterList[i].xPos -1][monsterList[i].yPos] == '+'))
                {
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].lastTile;
                    monsterList[i].xPos--;
                    if(test.Map[monsterList[i].xPos][monsterList[i].yPos] == '.' || test.Map[monsterList[i].xPos][monsterList[i].yPos] == '+')
                        monsterList[i].dominantTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;
                }
                if(abs((monsterList[i].xPos+1) - newPlayer.xPos) < abs(monsterList[i].xPos - newPlayer.xPos) && (test.Map[monsterList[i].xPos +1][monsterList[i].yPos] == '.' || test.Map[monsterList[i].xPos +1][monsterList[i].yPos] == '+'))
                {
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].lastTile;
                    monsterList[i].xPos++;
                    if(test.Map[monsterList[i].xPos][monsterList[i].yPos] == '.' || test.Map[monsterList[i].xPos][monsterList[i].yPos] == '+')
                        monsterList[i].dominantTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;
                }
                if(abs((monsterList[i].yPos+1) - newPlayer.yPos) < abs(monsterList[i].yPos - newPlayer.yPos) && (test.Map[monsterList[i].xPos][monsterList[i].yPos + 1] == '.' || test.Map[monsterList[i].xPos][monsterList[i].yPos +1] == '+'))
                {
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].lastTile;
                    monsterList[i].yPos++;
                    if(test.Map[monsterList[i].xPos][monsterList[i].yPos] == '.' || test.Map[monsterList[i].xPos][monsterList[i].yPos] == '+')
                        monsterList[i].dominantTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;
                }
                if(abs((monsterList[i].yPos-1) - newPlayer.yPos) < abs(monsterList[i].yPos - newPlayer.yPos) && (test.Map[monsterList[i].xPos][monsterList[i].yPos - 1] == '.' || test.Map[monsterList[i].xPos][monsterList[i].yPos -1] == '+'))
                {
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].lastTile;
                    monsterList[i].yPos--;
                    monsterList[i].lastTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    if(test.Map[monsterList[i].xPos][monsterList[i].yPos] == '.' || test.Map[monsterList[i].xPos][monsterList[i].yPos] == '+')
                        monsterList[i].dominantTile = test.Map[monsterList[i].xPos][monsterList[i].yPos];
                    test.Map[monsterList[i].xPos][monsterList[i].yPos] = monsterList[i].symbol;
                }
                else;

            }
    }


}


