#include "monsters.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>


newMonster selectMonster()
{
    int monsterType = rand()%4 + 1;
    newMonster mob;

    switch(monsterType)
    {
    case 1: //spider
    {
        mob.symbol = 'x';
        mob.health = 5;
        mob.armour = 0;
        mob.attackDamage = 2;
        mob.behaviourType = 1; // random movement
        break;
    }
    case 2: //goblin
    {
        mob.symbol = 'G';
        mob.health = 10;
        mob.armour = 2;
        mob.attackDamage = 3;
        mob.behaviourType = 2;
        break; //mindless seeking
    }
    case 3://bat
    {
        mob.symbol = 'B';
        mob.health = 7;
        mob.armour = 1;
        mob.attackDamage = 1;
        mob.behaviourType = 1;
        break; //random movement
    }
    case 4:
    {
        mob.symbol = 'T';
        mob.health = 15;
        mob.armour = 4;
        mob.attackDamage = 3;
        mob.behaviourType = 3;
    }
    }
    return mob;
}

void createMonster(newMonster monsterList[16])
{
    for(int i = 0; i < 16; i++)
    {
        newMonster mob = selectMonster();
        monsterList[i].armour = mob.armour;
        monsterList[i].health = mob.health;
        monsterList[i].behaviourType = mob.behaviourType;
        monsterList[i].symbol = mob.symbol;
        monsterList[i].attackDamage = mob.attackDamage;
        monsterList[i].ID = i;
        monsterList[i].gaveExp = 0;
    }

}

void placeMonsters(Generator &test, char &lastTile, newMonster monsterList[16])
{
    for(int i = 0; i < test.endRoomCount; i++)
    {
        int xPos = rand()%test.roomWidth[i]+1;
        int yPos = rand()%test.roomHeight[i]+1;
        monsterList[i].xPosInit = xPos;
        monsterList[i].yPosInit = yPos;
        monsterList[i].xPos = xPos + test.fRoomEdgesX[i];
        monsterList[i].yPos = yPos + test.fRoomEdgesY[i];

        if(xPos + test.fRoomEdgesX[i] >= test.lRoomEdgesX[i])
        {
            xPos = xPos - 3;
            monsterList[i].xPos -= 3;
        }

        if(yPos + test.fRoomEdgesY[i] >= test.lRoomEdgesY[i])
        {
            yPos = yPos - 3;
            monsterList[i].yPos -= 3;
        }

        if(test.Map[xPos + test.fRoomEdgesX[i]][yPos + test.fRoomEdgesY[i]] == '.')
        {
            monsterList[i].lastTile = test.Map[test.fRoomEdgesX[i] + xPos][test.fRoomEdgesY[i] + yPos];
            monsterList[i].dominantTile = test.Map[test.fRoomEdgesX[i] + xPos][test.fRoomEdgesY[i] + yPos];
            test.Map[test.fRoomEdgesX[i] + xPos][test.fRoomEdgesY[i] + yPos] = monsterList[i].symbol;
            monsterList[i].placedCorrectly = 1;

        }
        else
        {
            monsterList[i].placedCorrectly = 0;
            //test.Map[xPos + test.fRoomEdgesX[i]][test.fRoomEdgesY[i] + yPos] = 'E';
        }

    }
}
