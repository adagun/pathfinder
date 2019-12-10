//
// Created by adam on 2018-12-16.
//

#include "Pathfinder.h"
#include <algorithm>
#include <unordered_set>
#include <iostream>


Pathfinder::Pathfinder(Grid *grid, int x, int y) : m_grid(grid), m_x(x), m_y(y)
{
    m_targetX = -1;
    m_targetY = -1;
}


// uses the a* algorithm to find the closest path between two nodes
void Pathfinder::findPath(int targetX, int targetY)
{

    m_targetX = targetX;
    m_targetY = targetY;
    Node *startNode = m_grid->getNode(m_x, m_y);
    Node *targetNode = m_grid->getNode(targetX, targetY);



    std::vector<Node*> openList;
    std::vector<Node*> closedList;

    // add start node to the open list
    openList.push_back(startNode);


    while(!openList.empty())
    {
        // find the node with the lowest f cost and make it the current node
        Node *currentNode;

        for(int i = 0; i < openList.size(); i++)
        {
            // sort vector by lowest first
            std::sort(openList.begin(), openList.end(), [ ]( const auto& lhs, const auto& rhs )
            {
                return lhs->getFCost() < rhs-> getFCost();
            });
            currentNode = openList.front();
            // remove the node with the lowest f cost from open and add to the closed list
            openList.erase(openList.begin());
            closedList.push_back(currentNode);

            // target found retrace the path
            if(currentNode == targetNode)
            {
                retrace(startNode, targetNode);
                return;
            }

            std::vector<Node*> neighbours = m_grid->getNodeNeighbours(currentNode);
            // check neighbours
            for(Node *neighbour : neighbours)
            {

                // skip if neighbour is not walkable or in the closed list
               if(!neighbour->isWalkable() ||
                    std::find(closedList.begin(), closedList.end(), neighbour) != closedList.end() )
                {
                    continue;
                }


                int newCost = currentNode->getGCost() + m_grid->getDistance(currentNode, neighbour);
                // if  neighbour not in open set
                if(std::find(openList.begin(), openList.end(), neighbour) == openList.end())
                {
                    // add to open list
                    openList.push_back(neighbour);
                    // mark as searched by the pathfinder
                    m_grid->setSearched(neighbour);
                    // set f cost
                    neighbour->setGCost(newCost);
                    // set h cost
                    neighbour->setHCost(m_grid->getDistance(neighbour, targetNode ));
                    // set parent of neighbour to current
                    neighbour->setParent(currentNode);


                }
                // if neighbour is in the open list
                else if(std::find(openList.begin(), openList.end(), neighbour) != openList.end())
                {
                    // check if the new path is better
                    if(newCost < neighbour->getGCost())
                    {
                        // set parent
                        neighbour->setParent(currentNode);
                        // set f cost
                        neighbour->setGCost(newCost);
                        // set h cost
                        neighbour->setHCost(m_grid->getDistance(neighbour, targetNode ));


                    }
                }
            }
        }
    }

}

// starting from the end node, retrace the path by going through each node's parent and adding them to a stack
void Pathfinder::retrace(Node *start, Node *end)
{
    while(!m_path.empty())
    {
        m_path.pop();
    }
    Node *currentNode = end;
    while(currentNode != start)
    {
        m_path.push(currentNode);
        currentNode = currentNode->getParent();
    }
}


void Pathfinder::move()
{

    if(!m_path.empty())
    {
        Node *node = m_path.top();
        m_x = node->getX();
        m_y = node->getY();
        m_path.pop();
    }
}

void Pathfinder::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Pathfinder::setTarget(int x, int y)
{
    m_targetX = x;
    m_targetY = y;

}

std::stack<Node *> Pathfinder::getPath() const
{
    return m_path;
}


bool sortByFCost(const Node &lhs, Node &rhs)
{
    if(lhs.getFCost() < rhs.getFCost())
    {
        return true;
    }
    else if(lhs.getFCost() == rhs.getFCost() && lhs.getHCost() < rhs.getHCost())
    {
        return true;
    }
    return false;
}









