#include "Pacman.h"
#include "Mapa.h"
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

GLfloat alfa, beta; // Coordenadas e ângulos       
GLfloat raio = 0.5;
int triangulos = 20;

// Destrutor
Pacman::~Pacman(void) {}

// Construtor
Pacman::Pacman(double tx, double ty) {
  vidas      = 3;
  tx         = x;
  ty         = y;
  angulo     = 90;
  velocidade = 0.1;
  animacao   = false;
}

// Posição inicial do Pacman
void Pacman::Recomeca(void) {
  x        = 13.5;
  y        = 23;
  angulo   = 90;
  animacao = false;
}

// Move o Pacman na direção que estiver olhando
void Pacman::Move() {
  x +=  velocidade * cos(M_PI / 180 * angulo);
  y +=  velocidade * sin(M_PI / 180 * angulo);
}

// Desenha o Pacman
void Pacman::Desenha(void) {
  glColor3f(1, 1, 0);
  glPushMatrix();
  glTranslatef(x, -y, 0);
  glTranslatef(.5, 0.6, 0);
  glTranslatef((float)Mapa::MAPA_X / -2.0f, (float)Mapa::MAPA_Y / 2.0f, 0.5);
  GLfloat pacx, pacy, pacz = 0;
  
  for (alfa = 0.0; alfa < M_PI; alfa += M_PI/triangulos)
  {        
    glBegin(GL_TRIANGLE_STRIP);
    for (beta = 0.0; beta < 2.01*M_PI; beta += M_PI/triangulos)            
    {            
      pacx = raio*cos(beta)*sin(alfa);
      pacy = raio*sin(beta)*sin(alfa);
      pacz = raio*cos(alfa);
      glVertex3f(pacx, pacy, pacz);
      pacx = raio*cos(beta)*sin(alfa + M_PI/triangulos);
      pacy = raio*sin(beta)*sin(alfa + M_PI/triangulos);
      pacz = raio*cos(alfa + M_PI/triangulos);            
      glVertex3f(pacx, pacy, pacz);            
    }        
    glEnd();
  }
  
  glPopMatrix();
}
