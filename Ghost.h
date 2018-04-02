#ifndef _GHOST_H_
#define _GHOST_H_

#include <GL/glut.h>

class Ghost {
  private:

  public:
	
	bool edible;
	int edible_max_time;
	int edible_timer;
	

	bool eaten;

	bool transporting;


    float color[3];

	double speed;
	double max_speed;
	bool in_jail;
	int jail_timer;

	double angle;
	double x, y;

    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Ghost(double, double);

    // Destructor. Frees the display lists and texture object.
    ~Ghost(void);

	void Move(); //move the Ghost

	void Update(void);  //update ghost state

	void Chase(double, double, bool*);  //chase pacman

	bool Catch(double, double);	//collision detection

	void Reinit(void);

	void Vulnerable(void);

	//draw the Ghostman
	void Draw(void);

};


#endif
