#include <iostream>
#include <cstdlib>
#include <string>
#include "Generator.h"

using namespace std;

struct newItem
{
    string name;
    int itemType;
    int healthiness;
    int defensiveness;
    int regeneration;
    int damage;
    int ID;
};

int selectItemType();
newItem createItem(int type);
void itemArray(newItem itemList[500]);
string findDominantTrait(newItem itemList[500], int ID);
void printItemProperties(newItem itemList[500]);

