#ifndef _PACMAN_H_
#define _PACMAN_H_

class Pacman {
private:

  double velocidade;

public:

  int vidas;
  double angulo;
  double x, y;
  bool mover;

  Pacman(double, double);
  ~Pacman(void);
  void Move();
  void Recomeca();
  void Desenha(void);
};

#endif // ifndef _PACMAN_H_