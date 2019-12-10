//
// Created by adam on 2018-12-16.
//

#ifndef PROJEKT_PATHFINDER_H
#define PROJEKT_PATHFINDER_H

#include <stack>
#include "Grid.h"



// Handles the pathfinding
class Pathfinder
{

    Grid *m_grid;
    int m_x, m_y, m_targetX, m_targetY;
    std::stack<Node*> m_path;

public:

    Pathfinder() = default;
    Pathfinder(Grid *grid, int x, int y);
    void findPath(int targetX, int targetY);
    void retrace(Node *start, Node *end);
    int getX() const {return m_x;}
    int getY() const {return m_y;}
    void setPosition(int x, int y);
    void setTarget(int x, int y);
    int getTargetX() const{return m_targetX;};
    int getTargetY() const{return m_targetY;};
    void move();
    std::stack<Node*> getPath() const;


};


#endif //PROJEKT_PATHFINDER_H
