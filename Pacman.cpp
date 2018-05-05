// Bibliotecas
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Headers
#include "Mapa.h"
#include "Pacman.h"

// Coordenadas, ângulos e medidas
GLfloat alfa, beta;
GLfloat raio = 0.5;
GLfloat pacx, pacy, pacz = 0;
int triangulos = 20;

// Construtor
Pacman::Pacman(double tx, double ty) {
  vidas      = 3;
  tx         = x;
  ty         = y;
  angulo     = 90;
  velocidade = 0.1;
  mover      = false;
}

// Destrutor
Pacman::~Pacman(void) {}

// Posição inicial do Pacman
void Pacman::Recomeca(void) {
  x        = 13.5;
  y        = 23;
  angulo   = 90;
  mover    = false;
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
  
  // Desenha a esfera com triângulos
  for (alfa = 0.0; alfa < M_PI; alfa += M_PI/triangulos)
  {        
    glBegin(GL_TRIANGLE_STRIP);
    for (beta = 0.0; beta < 2.01 * M_PI; beta += M_PI / triangulos)     
    {            
      pacx = raio * cos(beta) * sin(alfa);
      pacy = raio * sin(beta) * sin(alfa);
      pacz = raio * cos(alfa);
      glVertex3f(pacx, pacy, pacz);

      pacx = raio * cos(beta) * sin(alfa + M_PI/triangulos);
      pacy = raio * sin(beta) * sin(alfa + M_PI/triangulos);
      pacz = raio * cos(alfa + M_PI/triangulos); 
      glVertex3f(pacx, pacy, pacz);            
    }        
    glEnd();
  }
  glPopMatrix();

  // Desenha a quantidade de vidas do Pacman
  for (int i = 0; i < vidas - 1; i++)
  {
    glPushMatrix();
    glTranslatef((float)Mapa::MAPA_X / -2.0f + i * 2, (float) Mapa::MAPA_Y / 2.0f + 3, 1);
    
    for (alfa = 0.0; alfa < M_PI; alfa += M_PI / triangulos)
    {        
      glBegin(GL_TRIANGLE_STRIP);
      for (beta = 0.0; beta < 2.01*M_PI; beta += M_PI / triangulos)     
      {            
        pacx = raio * cos(beta) * sin(alfa);
        pacy = raio * sin(beta) * sin(alfa);
        pacz = raio * cos(alfa);
        glVertex3f(pacx, pacy, pacz);

        pacx = raio * cos(beta) * sin(alfa + M_PI / triangulos);
        pacy = raio * sin(beta) * sin(alfa + M_PI / triangulos);
        pacz = raio * cos(alfa + M_PI / triangulos); 
        glVertex3f(pacx, pacy, pacz);            
      }        
      glEnd();
    }
    glPopMatrix();
  }
}