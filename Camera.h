#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL/glut.h>

class Camera {
private:

public:

  Camera(float);
  ~Camera(void);
  void Posicao(float, float, double);
};

#endif