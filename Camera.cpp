#include "Camera.h"
#include "Mapa.h"
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

// Destrutor
Camera::~Camera(void) {}

// Construtor
Camera::Camera(float ratio) {
  glEnable(GL_CULL_FACE);

  double eye[3];
  float  color[4], dir[4];

  // Enable lighting with one light.
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  // Ambient and diffuse lighting track the current color.
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  // Turn on normal vector normalization. You don't have to give unit
  // normal vector, and you can scale objects.
  glEnable(GL_NORMALIZE);

  color[0] = 1.0f;
  color[1] = 1.0f;
  color[2] = 1.0f;
  color[3] = 1.0f;
  glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
  color[0] = 0.0f;
  color[1] = 0.0f;
  color[2] = 0.0f;
  color[3] = 1.0f;
  glLightfv(GL_LIGHT0, GL_SPECULAR, color);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, ratio, 0.005, 100);
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

void Camera::Posicao(float x_at, float y_at, double angle, int view) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0f, 1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-1.5, -26, 25,
            -1.5,   -9,    1,
            0.0f, 0.0f, 1.0f);
}
