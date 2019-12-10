//
// Created by adam on 2018-12-14.
//

#ifndef PROJEKT_GAME_H
#define PROJEKT_GAME_H


#include "Grid.h"
#include "Pathfinder.h"

class Game
{


public:
    enum Direction{ up, down, left, right};

    Game(int gridSizeX, int gridSizeY);


    void drawGrid();
    void drawSquare(int x, int y);
    void drawPlayer();
    void move(Direction direction);

    void setWalkable();
    void findPath();
    void drawPathfinder();
    void drawPath();
    Grid *getGrid();
    void drawSearched();
    void movePathfinder();

    void reset();
    void createObstacles();
    bool targetHasMoved();
    int getRandom(int max);

private:

    int m_playerX, m_playerY;
    Pathfinder m_pathfinder;
    Grid m_grid;

};


#endif //PROJEKT_GAME_H
