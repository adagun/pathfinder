//
// Created by adam on 2018-12-16.
//

#include "Grid.h"
#include <cstdlib>
#include <iostream>


Grid::Grid(int sizeX, int sizeY)
{
    m_sizeX = sizeX;
    m_sizeY = sizeY;

    m_nodes.resize(sizeX);
    for(int i = 0; i < sizeX; i++)
    {
        m_nodes[i].resize(sizeY);
    }


    for(int x = 0; x < sizeX; x++)
    {
        for(int y = 0; y < sizeY; y++)
        {
            Node newNode = Node(x,y);
            m_nodes[x][y] = newNode;
        }
    }
}


int Grid::getSizeX() const
{
    return  m_sizeX;
}

int Grid::getSizeY() const
{
    return  m_sizeY;
}




Node* Grid::getNode(int x, int y)  {
    return &m_nodes[x][y];
}

// toggles walkable/unwalkable
void Grid::setWalkable(int x, int y)
{
    m_nodes[x][y].setWalkable(!m_nodes[x][y].isWalkable());

}


// find all of a nodes neighbours and return them in a vector
std::vector<Node*> Grid::getNodeNeighbours(Node *node)
{
    std::vector<Node*> neighbours;

    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            if(x == 0 && y == 0)
            {
                continue;
            }
            if(node->getX()+x >= 0 && node->getX()+x <= m_sizeX-1 &&
               node->getY()+y >= 0 && node->getY()+y <= m_sizeY-1)
            {
                neighbours.push_back(&m_nodes[node->getX()+x][node->getY()+y]);
            }
        }
    }

    return neighbours;
}

int Grid::getDistance(Node *from, Node *to)
{
    // Lowest number of x or y steps will give how many diagonal moves is needed to be in line with the target
    // the higher number minus the lower number will give the remaining steps needed to reach the target node



    // vertical/horizontal step is 10 units
    // diagonal step is 14 units.  (square root of two steps)
    // so the distance equation will be 14y + 10(x-y) or 14x + 10(y-x)

    int xDistance = abs(from->getX() - to->getX());
    int yDistance = abs(from->getY() - to->getY());

    if(xDistance > yDistance)
    {
        return 14*yDistance + 10 * (xDistance - yDistance);
    }
    return 14*xDistance + 10 * (yDistance - xDistance);
}

void Grid::addNodeToPath(Node * node)
{
    m_path.push_back(node);
}

std::vector<Node *> Grid::getPath()
{
    return m_path;
}

void Grid::resetPath()
{
    m_path.clear();

}

void Grid::reset()
{
    resetPath();
    for(auto& row : m_nodes)
    {
        for(auto& node : row)
        {
            node.setWalkable(true);
        }
    }

}

void Grid::setSearched(Node *node)
{
    m_searched.push_back(node);
}

std::vector<Node *> Grid::getSearched() const {
    return m_searched;
}

void Grid::clearSearched()
{
    m_searched.clear();
}





