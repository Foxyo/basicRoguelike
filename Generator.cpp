#include "Generator.h"
#include <iostream>
using namespace std;


void Generator::connect(int room2, int room1)
{
    char room1p = room1 + 48;
    char room2p = room2 + 48;

    int room1x, room1y, room2x, room2y;
    int found = 0;
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(Map[x][y] == 'D' && logicMap[x][y] == room1p)
            {
                room1x = x;
                room1y = y;
                found++;
            }
            else if(Map[x][y] == 'D' && logicMap[x][y] == room2p)
            {
                room2x = x;
                room2y = y;
                found++;
            }
        }
    }
    if(found == 2)
    {
        int x;
        if(room1x > room2x)
            x = room1x;
        else x = room2x;
        if(room1x > room2x)
        {
            for(int x = room2x+1; x!=room1x+1; x++)
            {
                if(Map[x][room2y]!= 'D' && Map[x][room2y]!='.')
                    Map[x][room2y] = 'o';
            }

        }
        else if(room2x > room1x)
        {
            for(int x = room1x+1; x!=room2x+1; x++)
            {
                if(Map[x][room1y]!= 'D' && Map[x][room1y]!='.')
                    Map[x][room1y] = 'o';
            }

        }
        if(room1y > room2y)
        {
            for(int y = room2y; y!=room1y; y++)
            {
                if(Map[x][y]!= 'D' && Map[x][y]!='.')
                    Map[x][y] = 'o';
            }

        }
        else if(room2y > room1y)
        {
            for(int y = room1y; y!=room2y; y++)
            {
                if(Map[x][y] != 'D' && Map[x][y]!='.')
                    Map[x][y] = 'o';
            }

        }
    }
}

void Generator::addFlush()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            Add[x][y] = ' ';
        }
    }
}

void Generator::addDoor(int roomWidth, int roomHeight, int edgeX, int edgeY)
{
    int doors = 1;
    int lineType = rand()%3 + 1;
    int x, y;
    switch(doors)
    {
    case 1:
        switch(lineType)
        {
        case 1:
        {
            x = rand()%roomWidth;
            if(x == 0)
                x = x + 2;
            if(x == 1)
                x = x + 1;
            if(x == roomWidth - 1)
                x = x - 1;
            Add[x + edgeX][edgeY] = 'D';
            break;
        }      // horizontal_up
        case 2:      // horizontal down
        {
            x = rand()%roomWidth;
            if(x == 0)
                x = x + 2;
            if(x == 1)
                x = x + 1;
            if(x == roomWidth - 1)
                x = x - 1;
            Add[x + edgeX][edgeY+roomHeight-1] = 'D';
            break;
        }
        case 3://vertical left
        {
            y = rand()%roomHeight;
            if(y == 0)
                y = y + 2;
            if(y == 1)
                y = y + 1;
            if(y == roomHeight - 1)
                y = y - 1;
            Add[edgeX][edgeY + y] = 'D';
            break;
        }
        case 4: // verticalRight
        {
            y = rand()%roomHeight;
            if(y == 0)
                y = y + 2;
            if(y == 1)
                y = y + 1;
            if(y == roomHeight - 1)
                y = y - 1;
            Add[edgeX + roomWidth -1][edgeY + y] = 'D';
            break;
        }
        }
        break;
    }
}

int Generator::edgeGen(int roomCount, int tries)
{
    //int s = time(0) + tries;
    //srand(s);
    int edgeX = rand()%map_width+2;
    int edgeY = rand()%map_height+2;
    int chcksm;
    chcksm = roomGen(edgeX, edgeY, roomCount, tries);
    if(chcksm == 1)
        return 1;
    if(chcksm == 2)
        return 2;
    else return 0;
}

int Generator::roomGen(int edgeX, int edgeY, int roomCount, int tries)
{
    //int s = time(0) + tries;
    //srand(s);
    int width, heigth;
    width = rand()%20 + 5 - 2*roomCount;
    if(width<5)
        width = abs(width) + 5;
    if(width + edgeX > map_width-1)
    {
        return 0;
    }

    heigth = rand()%5 + 5;
    if(heigth < 5)
        heigth = abs(heigth) + 5;
    if(heigth + edgeY > map_height-1)
    {
        return 0;
    }


    int validity;
    int res = checkIfValidInit(width, heigth, edgeX, edgeY);
    if(res != 1)
        return 0;

    for(int y = 0; y < heigth; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(y == 0 || x == 0 || x == width-1 || y == heigth -1)
                Add[x+edgeX][y+edgeY] = '#';
            else
                Add[x+edgeX][y+edgeY] = '.';
        }
    }

    if(checkIfValid() == 1)
        validity = 0;
    else validity = 1;
    if(validity == 1)
    {
        addFlush();
        return 2;
    }
    if(validity == 0)
    {
        fRoomEdgesX[roomCount] = edgeX;
        fRoomEdgesY[roomCount] = edgeY;
        lRoomEdgesX[roomCount] = edgeX + width - 1;
        lRoomEdgesY[roomCount] = edgeY + heigth - 1;
        roomWidth[roomCount] = width;
        roomHeight[roomCount] = heigth;

        addDoor(width, heigth, edgeX, edgeY);
        copyAddToMap();
        copyMapToLogic();
        logicMapFill(roomCount);
        addFlush();
        return 1;
    }

}

void Generator::copyMapToLogic()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(logicMap[x][y] == ' ' && Map[x][y]!= 'o')
                logicMap[x][y] = Map[x][y];
        }
    }
}

void Generator::copyMapToLogic1()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            logicMap[x][y] = Map[x][y];
        }
    }
}

void Generator::mapFill()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            Map[x][y] = ' ';
        }
    }
}

void Generator::logicMapDraw()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            cout << logicMap[x][y];
        }
        cout << "\n";
    }
}

void Generator::logicMapFill(int roomCount)
{
    char room = roomCount + 48;

    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(logicMap[x][y]=='o')
                logicMap[x][y] = ' ';
            if(logicMap[x][y] == '#' || logicMap[x][y] == '.' || logicMap[x][y] == 'D')
                logicMap[x][y] = room;
        }
    }
}

void Generator::copyMapToAdd()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            Add[x][y] = Map[x][y];
        }
    }
}

void Generator::copyAddToMap()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(Add[x][y]!= ' ')
                Map[x][y] = Add[x][y];
        }
    }
}

void Generator::flipOsToDot()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(Map[x][y] ==  'o')
                Map[x][y] = '.';
        }
    }
}

int Generator::checkIfValidInit(int width, int heigth, int edgeX, int edgeY)
{
    if(Map[edgeX][edgeY] != ' ')
        return 0;
    if(Map[edgeX+width][edgeY] != ' ')
        return 0;
    if(Map[edgeX][edgeY+heigth] != ' ')
        return 0;
    if(Map[edgeX + width][edgeY+heigth] != ' ')
        return 0;

    else return 1;
}

int Generator::checkIfValid()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(Add[x][y] == '.' && Map[x][y] == 'o')
                return 0;
            if(Add[x][y] == '#' && Map[x][y] == 'o')
                return 0;
            if(Add[x][y] == Map[x][y] && Map[x][y]!=' ' && Add[x][y]!=' ')
                return 0;
        }
    }
    return 1;
}

void Generator::makeWalls()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(Map[x][y] == 'D')
                Map[x][y] = '.';
            if(Map[x][y] == '.')
            {
                if(Map[x+1][y] == ' ')
                    Map[x+1][y] = '#';
                if(Map[x-1][y] == ' ')
                    Map[x-1][y] = '#';
                if(Map[x][y+1] == ' ')
                    Map[x][y+1] = '#';
                if(Map[x][y-1] == ' ')
                    Map[x][y-1] = '#';
            }

        }
    }
}

int Generator::placeLadder(int roomCount)
{
    char lastRoom = roomCount + 48;
    int firstR0x, firstR0y;
    int lastR0x, lastR0y;
    int firstRRx, firstRRy;
    int lastRRx, lastRRy;
    int R0guard = 0;
    int RRguard = 0;

    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(logicMap[x][y] == '0'  && R0guard == 0)
            {
                firstR0x = x+1;
                firstR0y = y+1;
                R0guard = 1;
            }
            else if(logicMap[x][y] == '0' && R0guard!=0)
            {
                lastR0x = x-1;
                lastR0y = y-1;
            }
            if(logicMap[x][y] == lastRoom  && RRguard == 0)
            {
                firstRRx = x+1;
                firstRRy = y+1;
                RRguard = 1;
            }
            else if(logicMap[x][y] == lastRoom  && RRguard!=0)
            {
                lastRRx = x-1;
                lastRRy = y-1;
            }
        }
    }

    // int s = time(0);
    //srand(s);

    int fxRange = lastR0x - firstR0x;
    int fyRange = lastR0y - firstR0y;
    int lxRange = lastRRx - firstRRx;
    int lyRange = lastRRy - firstRRy;
    if(fxRange <=0 || fyRange <=0 || lxRange<=0 || lyRange<=0)
        return 0;
    int firstLadderX = rand()%fxRange;
    int firstLadderY = rand()%fyRange;
    int lastLadderX = rand()%lxRange;
    int lastLadderY = rand()%lyRange;;

    Map[firstLadderX + firstR0x][firstLadderY + firstR0y] = 'H';
    ladderxPos[0] = firstLadderX + firstR0x;
    ladderyPos[0] = firstLadderY + firstR0y;
    Map[lastLadderX + firstRRx][lastLadderY + firstRRy] = 'H';
    ladderxPos[1] = lastLadderX + firstRRx;
    ladderyPos[1] = lastLadderY + firstRRy;
}

void Generator::Generate()
{
    mapFill();
    copyMapToLogic1();
    copyMapToAdd();

    int tries = 0;
    int invalidRmPlcmnt = 0;
    int chcksm;
    int roomCount = 0;
    int s = time(0);
    srand(s);
    int roomCountNum = rand()%15 + 10;

    do
    {
        chcksm = edgeGen(roomCount, tries);
        if(chcksm == 1)
            roomCount++;
        if(roomCount > 1)
            connect(roomCount-1, roomCount-2);
        if(chcksm == 2)
            invalidRmPlcmnt++;
        tries++;
        if(tries>3000 || invalidRmPlcmnt == 3000)
            break;
    }
    while(roomCount!=roomCountNum);

    flipOsToDot();
    connect(roomCount-1, roomCount-2);
    makeWalls();
    placeLadder(roomCount-1);
    makeDoorsHappen();

    endRoomCount = roomCount;

}

void Generator::mapDraw()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(Map[x][y] == '#')
                cout << "\033[0;33m" << Map[x][y];
            if(Map[x][y] == 'H')
                cout << "\033[0;31m" << Map[x][y];
            if(Map[x][y] == '@')
                cout << "\033[0;35m" << Map[x][y];
            if(Map[x][y]!='#' && Map[x][y]!='H' && Map[x][y]!='@')
                cout << "\033[0m" << Map[x][y];
        }
        cout << "\n";
    }
}

int Generator::countAdjacentWalls(int x, int y)
{
    int adjacentWalls = 0;

    if(Map[x-1][y] == '#')
        adjacentWalls++;
    if(Map[x][y-1] == '#')
        adjacentWalls++;
    if(Map[x][y+1] == '#')
        adjacentWalls++;
    if(Map[x+1][y] == '#')
        adjacentWalls++;

    return adjacentWalls;

}

void Generator::makeDoorsHappen()
{
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            if(logicMap[x][y] == ' ' && Map[x][y] == '.' && Map[x-1][y] =='.' && logicMap[x-1][y]!=' ' && countAdjacentWalls(x-1,y) == 2)
                Map[x-1][y] = '+';
            if(logicMap[x][y] == ' ' && Map[x][y] == '.' && Map[x+1][y] =='.' && logicMap[x+1][y]!=' ' && countAdjacentWalls(x+1,y) == 2)
                Map[x+1][y] = '+';
            if(logicMap[x][y] == ' ' && Map[x][y] == '.' && Map[x][y+1] =='.' && logicMap[x][y+1]!=' ' && countAdjacentWalls(x,y+1) == 2)
                Map[x][y+1] = '+';
            if(logicMap[x][y] == ' ' && Map[x][y] == '.' && Map[x][y-1] =='.' && logicMap[x][y-1]!=' ' && countAdjacentWalls(x,y-1) == 2)
                Map[x][y-1] = '+';
        }
    }
}
int Generator::isLegitMove(int x, int y)
{
    if(Map[x][y] == '.' || Map[x][y] == 'H' || Map[x][y] == '+')
        return 1;
    else return 0;
}

int Generator::isLegitMoveMonster(int x, int y)
{
    if(Map[x][y] == '.' || Map[x][y] == '+')
        return 1;
    else return 0;
}

Generator::Generator()
{
    this->Generate();
}

