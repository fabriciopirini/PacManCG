// code by John Hollister 2005
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>

class Board {
private:

  GLubyte list[5]; // display lists for each wall

  void create_list_lib(void);

public:

  // int pebbles_left;

  // array for eating
  int tp_array[31][28];

  static const int BOARD_X;
  static const int BOARD_Y;

  Board(void);

  ~Board(void);

  // void tp_restore(void);

  void Draw(void);

  bool IsOpen(int,
              int);
};


#endif // ifndef _BOARD_H_
