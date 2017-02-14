#include <iostream>
#include <cstdlib>
#include <string>
#include "Generator.h"
#ifndef LISELLOCH_ITEMS_H
#define LISELLOCH_ITEMS_H


using namespace std;

struct newItem
{
    string name;
    char symbol;
    char dominantTile;
    int itemType;
    int healthiness;
    int defensiveness;
    int regeneration;
    int damage;
    int ID;
    int xPos;
    int yPos;
    int xPosInit;
    int yPosInit;
    int taken;
    int placedIndex;
    int backpackIndex;
    int isBPOccupied;
    string isWorn;
    int isWornNum;
    int bonusAddedYet = 0;
};

int selectItemType();
newItem createItem(int type);
void itemArray(newItem itemList[500]);
string findDominantTrait(newItem itemList[500], int ID);
void printItemProperties(newItem itemList[500]);
int placeItemsInRooms(newItem itemList[500], Generator& test, newItem placedItems[200]);
void printPlacedItems(newItem placedItems[200], Generator& test, int placedItemsTotal);
void printPlacedItemsInfo(newItem placedItems[200], int placedItemsTotal);


#endif // LISELLOCH_ITEMS_H

