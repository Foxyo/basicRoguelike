#include <iostream>
#include <cstdio>
#include "items.h"
#include <string>

/* itemTypes:

1 - armour
2 - weapon
3 - ring
4 - necklace

/*struct newItem;
{
    string name;
    itemType;
    healthiness;
    defensiveness;
    regeneration;
    damage;
};*/


int selectItemType()
{
    int itemType = rand()%4 + 1;
    return itemType;
}

string findDominantTrait(newItem itemList[500], int ID)
{
// 1 - health 2 - def 3 - reg 4 - dmg
    string name;
    int maxVal = itemList[ID].healthiness;
    int maxValType = 1;
    if(maxVal < itemList[ID].defensiveness)
    {
        maxVal = itemList[ID].defensiveness;
        maxValType = 2;
    }
    if(maxVal < itemList[ID].regeneration)
    {
        maxVal = itemList[ID].regeneration;
        maxValType = 3;
    }
    if(maxVal < itemList[ID].damage)
    {
       maxVal = itemList[ID].damage;
       maxValType = 4;
    }
    switch(maxValType)
    {
        case 1:
        {
            if(itemList[ID].itemType == 1)
                return name = "Armour of Healthiness";
            if(itemList[ID].itemType == 2)
                return name = "Sword of Healthiness";
            if(itemList[ID].itemType == 3)
                return name = "Ring of Healthiness";
            if(itemList[ID].itemType == 4)
                return name = "Necklace of Healthiness";
        }
        case 2:
        {
            if(itemList[ID].itemType == 1)
                return name = "Armour of Defence";
            if(itemList[ID].itemType == 2)
                return name = "Sword of Defence";
            if(itemList[ID].itemType == 3)
                return name = "Ring of Defence";
            if(itemList[ID].itemType == 4)
                return name = "Necklace of Defence";
        }
        case 3:
        {
            if(itemList[ID].itemType == 1)
                return name = "Armour of Regeneration";
            if(itemList[ID].itemType == 2)
                return name = "Sword of Regeneration";
            if(itemList[ID].itemType == 3)
                return name = "Ring of Regeneration";
            if(itemList[ID].itemType == 4)
                return name = "Necklace of Regeneration";
        }
        case 4:
        {
            if(itemList[ID].itemType == 1)
                return name = "Armour of Attack";
            if(itemList[ID].itemType == 2)
                return name = "Sword of Attack";
            if(itemList[ID].itemType == 3)
                return name = "Ring of Attack";
            if(itemList[ID].itemType == 4)
                return name = "Necklace of Attack";
        }

    }

}
newItem createItem()
{
    int type = selectItemType();
    newItem item;

    switch(type)
    {
        case 1:
        {
            item.itemType = 1;
            item.healthiness = rand()%20 - 10;
            item.defensiveness = rand()%10 - 5;
            item.regeneration = rand()%4 - 2;
            item.damage = rand()%2 - 2;
            //item.name = findDominantTrait(item);
            break;
        }
        case 2:
        {
            item.itemType = 2;
            item.healthiness = rand()%6 - 3;
            item.defensiveness = rand()%5 - 2;
            item.regeneration = rand()%3 - 1;
            item.damage = rand()%10 -5;
            //item.name = findDominantTrait(item);
            break;
        }
        case 3:
        {
            item.itemType = 3;
            item.healthiness = rand()%20 - 10;
            item.defensiveness = rand()%5 - 2;
            item.regeneration = rand()%10 - 3;
            item.damage = rand()%5 - 2;
            //item.name = findDominantTrait(item);
            break;
        }
        case 4:
        {
            item.itemType = 4;
            item.healthiness = rand()%20 - 10;
            item.defensiveness = rand()%5 - 2;
            item.regeneration = rand()%10 - 3;
            item.damage = rand()%5 - 2;
            //item.name = findDominantTrait(item);
            break;
        }
    }
    return item;
}

void itemArray(newItem itemList[500])
{
    for(int i = 0; i < 500; i++)
    {
        newItem item = createItem();
        itemList[i].itemType = item.itemType;
        itemList[i].healthiness = item.healthiness;
        itemList[i].defensiveness = item.defensiveness;
        itemList[i].regeneration = item.regeneration;
        itemList[i].ID = i;
        itemList[i].damage = item.damage;
        itemList[i].name = findDominantTrait(itemList, itemList[i].ID);
    }
}

void printItemProperties(newItem itemList[500])
{
    for(int i = 0; i < 500; i++)
    {
        cout << "Item name: " << itemList[i].name << endl;
        cout << "Item type: " << itemList[i].itemType << endl;
        cout << "Damage: " << itemList[i].damage << endl;
        cout << "Defence: " << itemList[i].defensiveness << endl;
        cout << "Regeneration: " << itemList[i].regeneration << endl;
        cout << "Health: " << itemList[i].healthiness << endl;
        cout << "ID: " << itemList[i].ID << endl;
    }
}