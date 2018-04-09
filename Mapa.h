#ifndef _MAPA_H_
#define _MAPA_H_

#include <GL/glut.h>

class Mapa {
private:

  GLubyte lista[5]; // Define uma lista para cada parede

  void Paredes(void);

public:

  static const int MAPA_X;
  static const int MAPA_Y;

  Mapa(void);
  ~Mapa(void);
  void Desenha(void);
  bool NaTela(int, int);
};

#endif // ifndef _MAPA_H_