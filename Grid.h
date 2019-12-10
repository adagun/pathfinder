//
// Created by adam on 2018-12-16.
//

#ifndef PROJEKT_GRID_H
#define PROJEKT_GRID_H


#include <vector>
#include "Node.h"

class Grid
{

public:
    Grid(int sizeX, int sizeY);
    Grid() = default;

    int getSizeX() const;
    int getSizeY() const;
    Node* getNode(int x, int y) ;
    std::vector<Node*> getNodeNeighbours(Node *node);
    void setWalkable(int x, int y);
    int getDistance(Node *from, Node *to);
    void addNodeToPath(Node* node);
    std::vector<Node*> getPath();

    void resetPath();
    void clearSearched();
    void reset();
    // marks a square that has been searched by the pathfinder
    void setSearched(Node* node);
    std::vector<Node*> getSearched() const;

private:

    std::vector<std::vector<Node>> m_nodes;
    std::vector<Node*> m_path;
    // contains the nodes checked by the pathfinder before finding the best path
    std::vector<Node*> m_searched;
    int m_sizeX, m_sizeY;

};


#endif //PROJEKT_GRID_H
