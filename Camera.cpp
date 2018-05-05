// Bibliotecas
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Headers
#include "Camera.h"
#include "Mapa.h"

// Construtor
Camera::Camera(float razao) {
  float  cor[4], dir[4];

  // Ativa iluminação com apenas uma fonte de luz
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  // Luz ambiente e difusa e a cor atual
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  // Ativa a normalização do vetor normal. 
  // Pode escalar objetos.
  glEnable(GL_NORMALIZE);

  cor[0] = 1.0f;
  cor[1] = 1.0f;
  cor[2] = 1.0f;
  cor[3] = 1.0f;
  glLightfv(GL_LIGHT0, GL_DIFFUSE, cor);

  cor[0] = 0.0f;
  cor[1] = 0.0f;
  cor[2] = 0.0f;
  cor[3] = 1.0f;
  glLightfv(GL_LIGHT0, GL_SPECULAR, cor);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, razao, 0.005, 100);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0f, 1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  dir[0] = 0.0;
  dir[1] = 1.0;
  dir[2] = 1.0;
  dir[3] = 0.0;
  glLightfv(GL_LIGHT0, GL_POSITION, dir);
}

// Destrutor
Camera::~Camera(void) {}

// Define a posição da câmera
void Camera::Posicao(int x, int y, float angulo) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0f, 1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-1.5,  -26,   25,
            -1.5,   -9,    1,
            0.0f, 0.0f, 1.0f);
}