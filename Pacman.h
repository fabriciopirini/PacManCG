#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <GL/glut.h>

class Pacman {
private:

  double velocidade;

public:

  int vidas;

  double angulo;
  double x, y;
  bool animacao;

  Pacman(double, double);
  ~Pacman(void);
  void Move();
  void Recomeca();
  void Desenha(void);
};

#endif // ifndef _PACMAN_H_