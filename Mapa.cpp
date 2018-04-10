#include "Mapa.h"
#include <stdio.h>
#include <GL/glut.h>

const int Mapa::MAPA_X = 31;
const int Mapa::MAPA_Y = 28;

// Mapa do Pacman
// Obs: A rotação é feita no sentido anti-horário
//  0 - Espaço vazio
//  1 - Parede 1
//  2 - Parede 1 (Rotação = 90)
//  3 - Parede 1 (Rotação = 180)
//  4 - Parede 1 (Rotação = 270)
//  5 - Parede 2
//  6 - Parede 2 (Rotação = 90)
//  7 - Parede 3
//  8 - Parede 3 (Rotação = 90)
//  9 - Parede 3 (Rotação = 180)
// 10 - Parede 3 (Rotação = 270)
// 11 - Parede 4
int matriz_mapa[Mapa::MAPA_X][Mapa::MAPA_Y] = {
  { 8, 5,  5,  5,  5,  5, 5,  5,  5,  5,  5,  5, 5,  1,  1, 5, 5,  5,  5,  5,  5, 5, 5,  5,  5,  5, 5,  7 },
  { 6, 0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  2,  4, 0, 0,  0,  0,  0,  0, 0, 0,  0,  0,  0, 0,  6 },
  { 6, 0,  8,  1,  1,  7, 0,  8,  1,  1,  1,  7, 0,  2,  4, 0, 8,  1,  1,  1,  7, 0, 8,  1,  1,  7, 0,  6 },
  { 6, 0,  2, 11, 11,  4, 0,  2, 11, 11, 11,  4, 0,  2,  4, 0, 2, 11, 11, 11,  4, 0, 2, 11, 11,  4, 0,  6 },
  { 6, 0,  9,  3,  3, 10, 0,  9,  3,  3,  3, 10, 0,  9, 10, 0, 9,  3,  3,  3, 10, 0, 9,  3,  3, 10, 0,  6 },
  { 6, 0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0, 0, 0,  0,  0,  0,  0, 0, 0,  0,  0,  0, 0,  6 },
  { 6, 0,  8,  1,  1,  7, 0,  8,  7,  0,  8,  1, 1,  1,  1, 1, 1,  7,  0,  8,  7, 0, 8,  1,  1,  7, 0,  6 },
  { 6, 0,  9,  3,  3, 10, 0,  2,  4,  0,  9,  3, 3, 11, 11, 3, 3, 10,  0,  2,  4, 0, 9,  3,  3, 10, 0,  6 },
  { 6, 0,  0,  0,  0,  0, 0,  2,  4,  0,  0,  0, 0,  2,  4, 0, 0,  0,  0,  2,  4, 0, 0,  0,  0,  0, 0,  6 },
  { 9, 5,  5,  5,  5,  7, 0,  2, 11,  1,  1,  7, 0,  2,  4, 0, 8,  1,  1, 11,  4, 0, 8,  5,  5,  5, 5, 10 },
  { 0, 0,  0,  0,  0,  6, 0,  2, 11,  3,  3, 10, 0,  9, 10, 0, 9,  3,  3, 11,  4, 0, 6,  0,  0,  0, 0,  0 },
  { 0, 0,  0,  0,  0,  6, 0,  2,  4,  0,  0,  0, 0,  0,  0, 0, 0,  0,  0,  2,  4, 0, 6,  0,  0,  0, 0,  0 },
  { 0, 0,  0,  0,  0,  6, 0,  2,  4,  0,  8,  5, 5,  1,  1, 5, 5,  7,  0,  2,  4, 0, 6,  0,  0,  0, 0,  0 },
  { 5, 5,  5,  5,  5, 10, 0,  9, 10,  0,  6,  0, 0,  0,  0, 0, 0,  6,  0,  9, 10, 0, 9,  5,  5,  5, 5,  5 },
  { 0, 0,  0,  0,  0,  0, 0,  0,  0,  0,  6,  0, 0,  0,  0, 0, 0,  6,  0,  0,  0, 0, 0,  0,  0,  0, 0,  0 },
  { 5, 5,  5,  5,  5,  7, 0,  8,  7,  0,  6,  0, 0,  0,  0, 0, 0,  6,  0,  8,  7, 0, 8,  5,  5,  5, 5,  5 },
  { 0, 0,  0,  0,  0,  6, 0,  2,  4,  0,  9,  5, 5,  5,  5, 5, 5, 10,  0,  2,  4, 0, 6,  0,  0,  0, 0,  0 },
  { 0, 0,  0,  0,  0,  6, 0,  2,  4,  0,  0,  0, 0,  0,  0, 0, 0,  0,  0,  2,  4, 0, 6,  0,  0,  0, 0,  0 },
  { 0, 0,  0,  0,  0,  6, 0,  2,  4,  0,  8,  1, 1,  1,  1, 1, 1,  7,  0,  2,  4, 0, 6,  0,  0,  0, 0,  0 },
  { 8, 5,  5,  5,  5, 10, 0,  9, 10,  0,  9,  3, 3, 11, 11, 3, 3, 10,  0,  9, 10, 0, 9,  5,  5,  5, 5,  7 },
  { 6, 0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  2,  4, 0, 0,  0,  0,  0,  0, 0, 0,  0,  0,  0, 0,  6 },
  { 6, 0,  8,  1,  1,  7, 0,  8,  1,  1,  1,  7, 0,  2,  4, 0, 8,  1,  1,  1,  7, 0, 8,  1,  1,  7, 0,  6 },
  { 6, 0,  9,  3, 11,  4, 0,  9,  3,  3,  3, 10, 0,  9, 10, 0, 9,  3,  3,  3, 10, 0, 2, 11,  3, 10, 0,  6 },
  { 6, 0,  0,  0,  2,  4, 0,  0,  0,  0,  0,  0, 0,  0,  0, 0, 0,  0,  0,  0,  0, 0, 2,  4,  0,  0, 0,  6 },
  { 2, 1,  7,  0,  2,  4, 0,  8,  7,  0,  8,  1, 1,  1,  1, 1, 1,  7,  0,  8,  7, 0, 2,  4,  0,  8, 1,  4 },
  { 2, 3, 10,  0,  9, 10, 0,  2,  4,  0,  9,  3, 3, 11, 11, 3, 3, 10,  0,  2,  4, 0, 9, 10,  0,  9, 3,  4 },
  { 6, 0,  0,  0,  0,  0, 0,  2,  4,  0,  0,  0, 0,  2,  4, 0, 0,  0,  0,  2,  4, 0, 0,  0,  0,  0, 0,  6 },
  { 6, 0,  8,  1,  1,  1, 1, 11, 11,  1,  1,  7, 0,  2,  4, 0, 8,  1,  1, 11, 11, 1, 1,  1,  1,  7, 0,  6 },
  { 6, 0,  9,  3,  3,  3, 3,  3,  3,  3,  3, 10, 0,  9, 10, 0, 9,  3,  3,  3,  3, 3, 3,  3,  3, 10, 0,  6 },
  { 6, 0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0, 0, 0,  0,  0,  0,  0, 0, 0,  0,  0,  0, 0,  6 },
  { 9, 5,  5,  5,  5,  5, 5,  5,  5,  5,  5,  5, 5,  5,  5, 5, 5,  5,  5,  5,  5, 5, 5,  5,  5,  5, 5, 10 }
};

// Destrutor
Mapa::~Mapa(void) {}

// Constrói as paredes do mapa
Mapa::Mapa(void) {
  Paredes();
}

// Define as paredes do mapa
void Mapa::Paredes(void) {
  // Parede 1: 1 face (norte)
  lista[1] = glGenLists(1);
  glNewList(lista[1], GL_COMPILE);

  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glEnd();
  glEndList();

  // Parede 2: 2 faces (norte, sul)
  lista[2] = glGenLists(1);
  glNewList(lista[2], GL_COMPILE);
  glBegin(GL_QUADS);

  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);

  glNormal3f(0.0f, -1.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glEnd();
  glEndList();

  // Parede 3: 2 faces (norte, leste)
  lista[3] = glGenLists(1);
  glNewList(lista[3], GL_COMPILE);
  glBegin(GL_QUADS);

  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);

  glNormal3f(1.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glEnd();
  glEndList();

  // Parede 4: 1 face (superior)
  lista[4] = glGenLists(1);
  glNewList(lista[4], GL_COMPILE);
  glBegin(GL_QUADS);

  glNormal3f(0.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  glEnd();
  glEndList();
}

void Mapa::Desenha(void) {
  glColor3f(0, 0, 1);

  for (int i = 0; i < MAPA_X; i++) {
    for (int j = 0; j < MAPA_Y; j++) {
      glColor3f(0, 0, 1);
      int aux = 0;
      glPushMatrix();

      glTranslatef(-(float)MAPA_X / 2.0f, -(float)MAPA_Y / 2.0f, 0);
      glTranslatef(j, MAPA_Y - i, 0);
      glPushMatrix();
      glTranslatef(0.5, 0.5, 0);

      
      if (matriz_mapa[i][j] == 1) {
        aux = 1;
      }
      else if (matriz_mapa[i][j] == 2) {
        glRotatef(90.0, 0, 0, 1);
        aux = 1;
      }
      else if (matriz_mapa[i][j] == 3) {
        glRotatef(180.0, 0, 0, 1);
        aux = 1;
      }
      else if (matriz_mapa[i][j] == 4) {
        glRotatef(270.0, 0, 0, 1);
        aux = 1;
      }
      else if (matriz_mapa[i][j] == 5) {
        aux = 2;
      }  
      else if (matriz_mapa[i][j] == 6) {
        glRotatef(90.0, 0, 0, 1);
        aux = 2;
      }
      else if (matriz_mapa[i][j] == 7) {
        aux = 3;
      }
      else if (matriz_mapa[i][j] == 8) {
        glRotatef(90.0, 0, 0, 1);
        aux = 3;
      }
      else if (matriz_mapa[i][j] == 9) {
        glRotatef(180.0, 0, 0, 1);
        aux = 3;
      }
      else if (matriz_mapa[i][j] == 10) {
        glRotatef(270.0, 0, 0, 1);
        aux = 3;
      }
      
      glScalef(1, 1, 0.5);
      glTranslatef(-0.5, -0.5, 0);
      glCallList(lista[aux]);
      glPopMatrix();

      // Define profundidade para que elementos com coordenadas menores fiquem na frente
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LESS);

      if ((aux != 0) || (matriz_mapa[i][j] == 11)) {
        glTranslatef(0, 0, -0.5);
        glCallList(lista[4]);
      }
      glPopMatrix();
    }
  }
}

// Retorna se o mapa está aberto ou não na tela
bool Mapa::NaTela(int x, int y) {
  if (matriz_mapa[y][x] > 0) {
    return false;
  }
  return true;
}
