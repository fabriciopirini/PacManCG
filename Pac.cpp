#include "Pac.h"
#include "Board.h"
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

// Destructor
Pac::~Pac(void) {}

// Constructor
Pac::Pac(double tx, double ty) {
  lives   = 3;
  tx      = x;
  ty      = y;
  angle   = 90;
  speed   = 0.1;
  animate = false;
}

// put pacman at starting position and angle
void
Pac::Reinit(void) {
  x       = 13.5;
  y       = 23;
  angle   = 90;
  animate = false;
}

// move pacman in the direction he's facing
void
Pac::Move() {
  x +=  speed * cos(M_PI / 180 * angle);
  y +=  speed * sin(M_PI / 180 * angle);
}

void
Pac::Draw(void) {
  // draw current pacman
  glColor3f(1, 1, 0);
  glPushMatrix();
  glTranslatef(x,                             -y,                           0);
  glTranslatef(.5,                            0.6,                          0);
  glTranslatef((float)Board::BOARD_X / -2.0f, (float)Board::BOARD_Y / 2.0f, 0.5);
  glutSolidSphere(.5, 10, 10);
  glPopMatrix();

  // draw remaining pacman lives above the board

  /*for (int i = 0; i < lives-1; i++)
     {
      glPushMatrix();
      glTranslatef((float)Board::BOARD_X/-2.0f + i*2, (float)
         Board::BOARD_Y/2.0f+3,1);
      glutSolidSphere(0.5,10,10);
      glPopMatrix();
     }*/
}
