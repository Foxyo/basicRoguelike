#include <cstdlib>
#include <time.h>
using namespace std;

#ifndef LISELLOCH_GENERATOR_H
#define LISELLOCH_GENERATOR_H

#define map_width 70
#define map_height 40

class Generator
{
public:
    Generator();
    void Generate();
    void mapDraw();
    void logicMapDraw();
    int isLegitMoveMonster(int x, int y);
    int isLegitMove(int x, int y);
    int endRoomCount;

    // Łatwo dostępna mapa
    char Map[map_width][map_height];
    char logicMap[map_width][map_height];
    int ladderxPos[2];
    int ladderyPos[2];

    int fRoomEdgesX[24];
    int fRoomEdgesY[24];
    int lRoomEdgesX[24];
    int lRoomEdgesY[24];
    int roomWidth[24];
    int roomHeight[24];

private:
    // Dane
    char Add[map_width][map_height];

    // Funkcje
    int countAdjacentWalls(int x, int y);
    void connect(int room2, int room1);
    void addFlush();
    void addDoor(int roomWidth, int roomHeight, int edgeX, int edgeY);
    int edgeGen(int roomCount, int tries);
    int roomGen(int edgeX, int edgeY, int roomCount, int tries);
    void copyMapToLogic();
    void copyMapToLogic1();
    void mapFill();
    void logicMapFill(int roomCount);
    void copyMapToAdd();
    void copyAddToMap();
    void flipOsToDot();
    int checkIfValidInit(int width, int heigth, int edgeX, int edgeY);
    int checkIfValid();
    void makeWalls();
    int placeLadder(int roomCount);
    void makeDoorsHappen();
};


#endif //LISELLOCH_GENERATOR_H
