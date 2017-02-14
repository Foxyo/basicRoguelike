#include <iostream>
#include <cstdlib>
#include <string>
#include "Generator.h"

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
};

int selectItemType();
newItem createItem(int type);
void itemArray(newItem itemList[500]);
string findDominantTrait(newItem itemList[500], int ID);
void printItemProperties(newItem itemList[500]);
int placeItemsInRooms(newItem itemList[500], Generator& test, newItem placedItems[200]);
void printPlacedItems(newItem placedItems[200], Generator& test, int placedItemsTotal);

