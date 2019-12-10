//
// Created by adam on 2018-12-16.
//

#include <iostream>
#include "Node.h"

// The node class represents a square in the grid
Node::Node(int x, int y)
{
    m_x = x;
    m_y = y;
    m_walkable = true;
    m_gCost = 0;
    m_hCost = 0;
    m_parent = nullptr;

}

void Node::setWalkable(bool walkable) {m_walkable = walkable;}

int Node::getX() const {return m_x;}

int Node::getY() const {return m_y;}

bool Node::isWalkable() const {return m_walkable;}

int Node::getFCost() const
{
    return m_gCost + m_hCost;
}

int Node::getGCost() const
{
    return m_gCost;
}

int Node::getHCost() const
{
    return m_hCost;
}

// compares nodes by coordinates
bool Node::operator==(const Node &n) const
{
    return (this->m_x == n.m_x && this->m_y == n.m_y);
}

void Node::setGCost(int cost)
{
    m_gCost = cost;
}

void Node::setHCost(int cost)
{
    m_hCost = cost;
}

void Node::setParent(Node *parent)
{
    m_parent = parent;
}

Node *Node::getParent() {
    return m_parent;
}


// Compares a node by f cost, if f costs are the same h costs are used
bool Node::operator<(const Node &n) const
{
    if(this->getFCost() < n.getFCost())
    {
        return true;
    }
    else if(this->getFCost() == n.getFCost() && this->m_hCost < n.m_hCost)
    {
        return true;
    }
    return false;
}







