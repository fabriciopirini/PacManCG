#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL/glut.h>

class Camera {
  private:

  public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Camera(float);

    // Destructor. Frees the display lists and texture object.
    ~Camera(void);

	void Set_position(float, float,double,int);
};


#endif
