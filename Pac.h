#ifndef _PAC_H_
#define _PAC_H_

#include <GL/glut.h>

class Pac {
  private:
	double speed;

  public:

    int lives;

	double angle;
	double x, y;
	bool animate;

    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Pac(double, double);

    // Destructor. Frees the display lists and texture object.
    ~Pac(void);

	void Move(); //move the pacman

	void Reinit();  //reinitialize everything

	//draw the pacman
	void Draw(void);

};


#endif
