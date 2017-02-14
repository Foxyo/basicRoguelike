#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "mainFuncts.h"

void handlePlayerStatus(player& newPlayer, newItem playerBackpack[30])
{
    for(int i = 0; i < 30; i++)
    {
        if(playerBackpack[i].isWornNum == 1 && playerBackpack[i].bonusAddedYet == 0)
        {
            playerBackpack[i].bonusAddedYet = 1;
            newPlayer.additionalHealth = playerBackpack[i].healthiness;
            newPlayer.armourDefence = playerBackpack[i].defensiveness;
            newPlayer.regeneration = playerBackpack[i].regeneration;
            newPlayer.weaponDamage = playerBackpack[i].damage;

            newPlayer.health += newPlayer.additionalHealth;
            newPlayer.attackDamage += newPlayer.weaponDamage;
            newPlayer.defence += newPlayer.armourDefence;
        }
        if(playerBackpack[i].isWornNum == 0 && playerBackpack[i].bonusAddedYet == 1)
        {
            playerBackpack[i].bonusAddedYet = 0;

            newPlayer.health -= newPlayer.additionalHealth;
            newPlayer.attackDamage -= newPlayer.weaponDamage;
            newPlayer.defence -= newPlayer.armourDefence;
            newPlayer.regeneration = 0;
        }

    }
    if(newPlayer.health < 100)
    newPlayer.health += newPlayer.regeneration;
}

int findLowerUnoccupiedBPIndex(newItem playerBackpack[30])
{
    int Index;

    for(int i = 0; i < 30; i++)
    {

        if(playerBackpack[i].isBPOccupied == 0)
        {
            Index = i;
            return Index;
        }

    }
}

void handlePlayerInput(player& newPlayer, char& lastTile, Generator& test, newMonster monsterList[16], newItem playerBackpack[30], newItem itemList[500], newItem placedItems[200], int& placedItemsTotal, int& levelsGenerated)
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
            itemArray(itemList);
            levelsGenerated++;
            test.visitedArrayInit();
            placedItemsTotal = placeItemsInRooms(itemList, test, placedItems);
            test.mapDraw();
        }
        if(isItem(test, newPlayer.xPos, newPlayer.yPos) == 1 && newPlayer.itemsOnPlayer < 30)
        {
            int IID = findPlacedItemIndex(newPlayer.xPos, newPlayer.yPos, test, placedItems);
            int index = findLowerUnoccupiedBPIndex(playerBackpack);
            playerBackpack[index] = placedItems[IID];
            playerBackpack[index].isBPOccupied = 1;
            playerBackpack[index].isWornNum = 0;
            playerBackpack[index].backpackIndex = index;
            newPlayer.itemsOnPlayer++;

            takeItem(test, newPlayer.xPos, newPlayer.yPos, placedItems, IID);
        }
        break;
    }
    case 'i':
    {
        printPlayerBackpack(playerBackpack, newPlayer);
        cout << "What would you like to do?" << endl;
        char c = getchar();
        switch(c)
        {
            case 'e':
            {
                cout << "stage1" << endl;
            int bpIndex;
            cout << "Provide backpack index of item you'd like to wear " << endl;
            cin >> bpIndex;
            cout << "stage2" << endl;

            if(playerBackpack[bpIndex].isBPOccupied == 1 && playerBackpack[bpIndex].isWornNum == 0)
            {
                cout << "stage3" << endl;
                if(newPlayer.isWearingRings!=2 && playerBackpack[bpIndex].itemType == 3)
                {
                    cout << "stage4" << endl;
                    playerBackpack[bpIndex].isWornNum = 1;
                    newPlayer.isWearingRings++;
                    break;
                } else if(newPlayer.isWearingRings == 2 && playerBackpack[bpIndex].itemType == 3)
                {
                    cout << "You're already wearing two rings, try something else!" << endl;
                    break;
                }
                if(newPlayer.isWieldingWeapon == 0 && playerBackpack[bpIndex].itemType == 2)
                {
                    cout << "stage5" << endl;
                    playerBackpack[bpIndex].isWornNum = 1;
                    newPlayer.isWieldingWeapon = 1;
                    break;
                }
                else if(newPlayer.isWieldingWeapon == 1 && playerBackpack[bpIndex].itemType == 2)
                {
                    cout << "You are already wielding a weapon, the heck you're trying to do, you're basically nobody, not a goddam rambo!" << endl;
                    break;
                }

                if(newPlayer.hasArmour == 0 && playerBackpack[bpIndex].itemType == 1)
                {
                    cout << "stage6" << endl;
                    playerBackpack[bpIndex].isWornNum = 1;
                    newPlayer.hasArmour = 1;
                    break;
                }
                else if(newPlayer.hasArmour == 1 && playerBackpack[bpIndex].itemType == 1)
                {
                    cout << "It ain't winter matey, aspiring to be a sumo-huge?" << endl;
                    break;
                }
                if(newPlayer.carriesNecklace == 0 && playerBackpack[bpIndex].itemType == 4)
                {
                    cout << "stage7" << endl;
                    playerBackpack[bpIndex].isWornNum = 1;
                    newPlayer.carriesNecklace = 1;
                    break;
                }
                else if(newPlayer.carriesNecklace == 1 && playerBackpack[bpIndex].itemType == 4)
                {
                    cout << "Wanna die from suffocation? It ain't your time yet. More is to come." << endl;
                    break;
                }

            }
            break;

            }

            case 'd':
            {
                int bpIndex;
                cout << "Which item(index) would you like to DELETE from inventory?" << endl;
                cin >> bpIndex;

                if(playerBackpack[bpIndex].itemType == 1)
                {
                    if(newPlayer.hasArmour >= 1)
                        newPlayer.hasArmour = 0;
                    if(newPlayer.itemsOnPlayer>=1)
                        newPlayer.itemsOnPlayer--;
                    playerBackpack[bpIndex].isWornNum = 0;
                    playerBackpack[bpIndex].isBPOccupied = 0;
                    break;
                }
                else if(playerBackpack[bpIndex].itemType == 2)
                {
                    if(newPlayer.isWieldingWeapon >= 1)
                        newPlayer.isWieldingWeapon = 0;
                    if(newPlayer.itemsOnPlayer>=1)
                        newPlayer.itemsOnPlayer--;
                    playerBackpack[bpIndex].isWornNum = 0;
                    playerBackpack[bpIndex].isBPOccupied = 0;
                    break;
                }
                else if(playerBackpack[bpIndex].itemType == 3)
                {
                    if(newPlayer.isWearingRings >= 1)
                        newPlayer.isWearingRings--;
                    if(newPlayer.itemsOnPlayer>=1)
                        newPlayer.itemsOnPlayer--;
                    playerBackpack[bpIndex].isWornNum = 0;
                    playerBackpack[bpIndex].isBPOccupied = 0;
                    break;
                }
                else if(playerBackpack[bpIndex].itemType == 4)
                {
                    if(newPlayer.carriesNecklace >= 1)
                        newPlayer.carriesNecklace = 0;
                    if(newPlayer.itemsOnPlayer>=1)
                        newPlayer.itemsOnPlayer--;
                    playerBackpack[bpIndex].isWornNum = 0;
                    playerBackpack[bpIndex].isBPOccupied = 0;
                    break;
                }

                break;

            }
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
       if(isMonster(newPlayer.xPos-1, newPlayer.yPos, test) == 1)
        {

            int ID = findMonsterID(newPlayer.xPos-1, newPlayer.yPos, monsterList);
            monstersInfoPrint(monsterList, test);
            attackMonster(ID, monsterList, newPlayer.attackDamage);
            checkIfDead(ID, monsterList, test, newPlayer);
        }
        break;
    }
    case 'd':
    {
       if(isMonster(newPlayer.xPos+1, newPlayer.yPos, test) == 1)
        {
            int ID = findMonsterID(newPlayer.xPos+1, newPlayer.yPos, monsterList);
            monstersInfoPrint(monsterList, test);
            attackMonster(ID, monsterList, newPlayer.attackDamage);
            checkIfDead(ID, monsterList, test, newPlayer);
        }
        break;
    }
    case 'w':
    {
       if(isMonster(newPlayer.xPos, newPlayer.yPos-1, test) == 1)
        {
            int ID = findMonsterID(newPlayer.xPos, newPlayer.yPos-1, monsterList);
            monstersInfoPrint(monsterList, test);
            attackMonster(ID, monsterList, newPlayer.attackDamage);
            checkIfDead(ID, monsterList, test, newPlayer);
        }
        break;
    }
    case 's':
    {
       if(isMonster(newPlayer.xPos, newPlayer.yPos+1, test) == 1)
        {
            int ID = findMonsterID(newPlayer.xPos, newPlayer.yPos+1, monsterList);
            monstersInfoPrint(monsterList, test);
            attackMonster(ID, monsterList, newPlayer.attackDamage);
            checkIfDead(ID, monsterList, test, newPlayer);
        }
        break;
    }

    }


    }
    }

    test.visitedArrayCalc(newPlayer.xPos, newPlayer.yPos);
    lastTile = test.Map[newPlayer.xPos][newPlayer.yPos];
    test.Map[newPlayer.xPos][newPlayer.yPos] = '@';
}
void takeItem(Generator& test, int x, int y, newItem placedItems[200], int IID)
{
    placedItems[IID].taken = 1;
    test.Map[x][y] = placedItems[IID].dominantTile;

}
int findPlacedItemIndex(int x, int y, Generator& test, newItem placedItems[200])
{
    int IID;
    for(int i = 0; i < 200; i++)
    {
        if(placedItems[i].xPos == x && placedItems[i].yPos == y)
        {
            IID = placedItems[i].placedIndex;
            return IID;
        }

    }
}

void printPlayerBackpack(newItem playerBackpack[30], player newPlayer)
{
    for(int i = 0; i < 30; i++)
    {
        if(playerBackpack[i].isBPOccupied == 1)
        {
        cout << "Item name: " << playerBackpack[i].name << endl;
        cout << "Item type: " << playerBackpack[i].itemType << endl;
        cout << "Damage: " << playerBackpack[i].damage << endl;
        cout << "Defence: " << playerBackpack[i].defensiveness << endl;
        cout << "Regeneration: " << playerBackpack[i].regeneration << endl;
        cout << "Health: " << playerBackpack[i].healthiness << endl;
        cout << "Index in backpack: " << playerBackpack[i].backpackIndex << endl;
        if(playerBackpack[i].isWornNum == 1)
            cout << "Currently wearing" << endl;
        cout << endl;
        }


    }

}

int isItem(Generator& test, int x, int y)
{
    if(test.Map[x][y] == 'A' || test.Map[x][y] == 'O' || test.Map[x][y] == '/' || test.Map[x][y] == 'U')
        return 1;
    else return 0;
}

int isMonster(int x, int y, Generator& test)
{
    if(test.Map[x][y] == 'G' || test.Map[x][y] == 'B' || test.Map[x][y] == 'x' || test.Map[x][y] == 'T')
        return 1;
    else return 0;
}

void checkIfDead(int ID, newMonster monsterList[16], Generator& test, player& newPlayer)
{
    if(monsterList[ID].health < 0 && monsterList[ID].gaveExp == 0)
    {
        test.Map[monsterList[ID].xPos][monsterList[ID].yPos] = monsterList[ID].dominantTile;
        monsterList[ID].xPos = 0;
        monsterList[ID].yPos = 0;
        newPlayer.monstersKilled++;
        if(monsterList[ID].symbol == 'G')
            newPlayer.experience += 5;
        if(monsterList[ID].symbol == 'B')
            newPlayer.experience += 3;
        if(monsterList[ID].symbol == 'x')
            newPlayer.experience += 2;
        if(monsterList[ID].symbol == 'T')
            newPlayer.experience += 20;


    }
}
void attackMonster(int ID, newMonster monsterList[16], int damage)
{
    int damageDealt = damage - monsterList[ID].armour;
    if(damageDealt < 1)
        damageDealt = 1;
    monsterList[ID].health -= damageDealt;
    monsterList[ID].behaviourType = 2;
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
void handleLevelUps(player& newPlayer)
{
    if(newPlayer.experience > 15)
    {
        newPlayer.experience = 0;
        newPlayer.attackDamage++;
        newPlayer.health += 5;
        newPlayer.defence += 1;
        newPlayer.level++;
    }

}

void displayPlayerInfo(player& newPlayer)
{
    cout << "Health: " << newPlayer.health << "    " << "Armor: " << newPlayer.defence << "    " << "Dmg: " << newPlayer.attackDamage << "    " <<  "Level: " << newPlayer.level << "    " << "Experience: " << newPlayer.experience << endl;
}
int isPlayer(int x, int y, Generator& test)
{
    if(test.Map[x+1][y] =='@' || test.Map[x-1][y] =='@' || test.Map[x][y+1] =='@' || test.Map[x][y-1] =='@')
        return 1;
    else return 0;
}

void handleMonsterActions(newMonster monsterList[16], Generator& test, player& newPlayer)
{
    for(int i = 0; i < 16; i++)
    {
        if(isPlayer(monsterList[i].xPos, monsterList[i].yPos, test) && monsterList[i].behaviourType == 2)
        {
            int damageDealt = monsterList[i].attackDamage - newPlayer.defence;
            if(damageDealt < 1)
                damageDealt = 1;
            newPlayer.health -= damageDealt;
        }
        else if(monsterList[i].behaviourType == 1 && monsterList[i].placedCorrectly == 1 && monsterList[i].health > 0)
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
        else if(monsterList[i].behaviourType == 2 && monsterList[i].placedCorrectly == 1 && monsterList[i].health > 0)
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

void wonOrLostMsg(int wonOrLost, player& newPlayer)
{
    cout << "\033[2J\033[1;1H";
    if(wonOrLost == 1)
    {

        cout << "Congratulations!" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "You did beat this awkward game, somewhat, somehow" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "On your way you've achieved level " << newPlayer.level << " collecting " << newPlayer.experience + newPlayer.level*15 << " Experience points!" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "You've also bested " << newPlayer.monstersKilled << " enemies!" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Good luck in future!" << endl;
        cout << "Press any key to contine" << endl;
        char a = getchar();
    }
    else
        cout << "YOU LOST" << endl;

}




