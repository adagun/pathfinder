//
// Created by adam on 2018-12-16.
//

#ifndef PROJEKT_SQUARE_H
#define PROJEKT_SQUARE_H

// represents a square in the game grid
class Node
{

    int m_x;
    int m_y;
    Node *m_parent;
    bool m_walkable;
    int m_gCost;
    int m_hCost;


public:
    Node() = default;
    Node(int x, int y);
    int getX() const;;
    int getY() const;;
    bool isWalkable() const;
    void setWalkable(bool walkable);
    int getFCost() const;
    int getGCost() const;
    int getHCost() const;
    void setParent(Node *parent);
    void setGCost(int cost);
    void setHCost(int cost);
    bool operator==(const Node &n) const;
    bool operator< (const Node &n) const;

    Node *getParent();
};






#endif //PROJEKT_SQUARE_H
