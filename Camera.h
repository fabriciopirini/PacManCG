#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL/glut.h>

class Camera {
private:

public:

  Camera(float);
  ~Camera(void);
  void Set_position(float,
                    float,
                    double,
                    int);
};

#endif // ifndef _CAMERA_H_
