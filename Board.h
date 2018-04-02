//code by John Hollister 2005
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>

class Board {
  private:
	GLubyte list[5];  //display lists for each wall

	void create_list_lib(void);

  public:

	int pebbles_left;

	//array for eating
	int tp_array[31][28];

	static const int BOARD_X;
	static const int BOARD_Y;

    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Board(void);

    // Destructor. Frees the display lists and texture object.
    ~Board(void);

	void tp_restore(void);

	//draw the board
	void Draw(void);


	//this function returns whether or not a location is open or a wall
	bool IsOpen(int, int);



};


#endif
