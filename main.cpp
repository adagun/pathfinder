
#include <GL/glut.h>
#include <GL/gl.h>
#include "Game.h"


// Callback functions
void display();
void keyboardSpecial(int key, int, int);
void keyboard(unsigned char c, int x, int y);
void reshape(int w, int h);
void timer(int);



// Grid size
const int gridSizeX = 50;
const int gridSizeY = 50;

const int FPS = 60;

Game g =  Game(gridSizeX, gridSizeY);

int main(int argc, char **argv)
{


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(300, 150);
    glutInitWindowSize(1280, 900);
    glutCreateWindow("A* Pathfinding");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    glutMainLoop();

    return 0;
}




void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    g.drawSearched();
    g.drawGrid();
    g.drawPath();
    g.drawPathfinder();
    g.drawPlayer();
    glutSwapBuffers();

}


void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, gridSizeX+1, -1, gridSizeY+1, -1, 1);
    glMatrixMode (GL_MODELVIEW);

}


void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, 0 );

}



void keyboard(unsigned char c, int x, int y)
{
    if (c == 27) // esc
    {
       exit(0);

    }
    else if(c == 32) // space
    {
        g.setWalkable();
    }
    else if(c == 70 || c == 102) // F
    {
        // calculate new path if needed
        if(g.targetHasMoved())
        {
            g.findPath();
        }
           g.movePathfinder();
    }

    else if(c == 82 || c == 114)  // R
    {
        g.reset();

    }
}



void keyboardSpecial(int key, int, int)
{
   switch(key)
   {
       case GLUT_KEY_UP:
       {
           g.move(Game::Direction::up);
           break;
       }
       case GLUT_KEY_DOWN:
       {
           g.move(Game::Direction::down);
           break;
       }
       case GLUT_KEY_LEFT:
       {
           g.move(Game::Direction::left);
           break;
       }
       case GLUT_KEY_RIGHT:
       {
           g.move(Game::Direction::right);
           break;
       }
   }

}

