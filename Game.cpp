//
// Created by adam on 2018-12-14.
//

#include <GL/gl.h>
#include <iostream>
#include "Game.h"
#include <algorithm>


Game::Game(int gridSizeX, int gridSizeY)
{
    m_grid = Grid(gridSizeX, gridSizeY);
    m_pathfinder = Pathfinder(&m_grid, getRandom(gridSizeX), getRandom(gridSizeY));
    createObstacles();
    m_playerX = getRandom(gridSizeX);
    m_playerY = getRandom(gridSizeY);
}




// draw a square in the grid
void Game::drawSquare(int x, int y)
{
    if(!m_grid.getNode(x, y)->isWalkable())
    {
        // non-walkable square
        glColor3f(0,0,1);
        glRectd(x, y, x+1, y+1);
    }
    // grid colour
    glColor3f(0.5,0.5,0.5);
    glLineWidth(1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x+1, y);
        glVertex2f(x+1, y+1);
        glVertex2f(x, y+1);
    glEnd();


}

void Game::drawGrid()
{
    for(int x = 0; x < m_grid.getSizeX(); x++)
    {
        for(int y = 0; y < m_grid.getSizeY(); y++)
        {
            drawSquare(x, y);
        }
    }


}

void Game::drawSearched()
{
    for(Node* node : m_grid.getSearched())
    {
        glColor3f(0.5, 0, 0.25);
        glRectd(node->getX(), node->getY(), node->getX()+1, node->getY()+1);
    }

}


void Game::drawPlayer()
{
    glColor3f(0, 1, 0);
    glRectd(m_playerX, m_playerY, m_playerX+1, m_playerY+1);

}

void Game::move(Game::Direction direction)
{

    switch (direction)
    {
        case Direction::up:
        {
            if(m_playerY < m_grid.getSizeY()-1 )
                    m_playerY++;
            break;
        }
        case Direction::down:
        {
            if(m_playerY > 0)
                m_playerY--;
            break;
        }
        case Direction::left:
        {
            if(m_playerX > 0)
                m_playerX--;
            break;
        }
        case Direction::right:
        {
            if(m_playerX < m_grid.getSizeX()-1)
                m_playerX++;
            break;
        }
    }

}

void Game::setWalkable()
{
    m_grid.setWalkable(m_playerX, m_playerY);
}



void Game::drawPathfinder()
{
    glColor3f(1, 0, 0);
    glRectd(m_pathfinder.getX(), m_pathfinder.getY(), m_pathfinder.getX()+1, m_pathfinder.getY()+1);

}

void Game::findPath()
{
    m_pathfinder.findPath(m_playerX, m_playerY);
}

void Game::movePathfinder()
{
    while(!m_pathfinder.getPath().empty())
    {
        m_grid.addNodeToPath(m_grid.getNode(m_pathfinder.getX(), m_pathfinder.getY()));
        m_pathfinder.move();
    }

}

void Game::drawPath()
{

    for(Node *node : m_grid.getPath())
    {
        glColor3f(1, 0, 1);
        glRectd(node->getX(), node->getY(), node->getX()+1, node->getY()+1);
    }

}



void Game::reset()
{
    m_grid.reset();
    m_grid.clearSearched();
    m_playerX = getRandom(m_grid.getSizeX());
    m_playerY = getRandom(m_grid.getSizeY());
    createObstacles();
    m_pathfinder.setPosition(getRandom(m_grid.getSizeX()), getRandom(m_grid.getSizeY()));
    m_pathfinder.setTarget(-1, -1);



}

// see if target has moved and path needs to be recalculated
bool Game::targetHasMoved()
{
    return m_playerX != m_pathfinder.getTargetX() || m_playerY != m_pathfinder.getTargetY();
}


// creates some randomised non-walkable squares on the grid
void Game::createObstacles()
{

    for(int i = 0; i < m_grid.getSizeX()*m_grid.getSizeY()/3; i++)
    {
        int y = getRandom(m_grid.getSizeY());
        int x = getRandom(m_grid.getSizeX());

        if(m_playerX != x && m_playerY != y)
        {
            m_grid.setWalkable(x, y);
        }


    }

}

int Game::getRandom(int max)
{
    return rand() % max;
}






