#ifndef _FANTASMA_H_
#define _FANTASMA_H_

class Fantasma {
public:

int tempo_vulneravel;
int tempoMax_vulneravel;
int tempo_preso;
double velocidade;
double velocidade_max;
double angulo;
double x, y;
float cor[3];
bool vulneravel;
bool pego;
bool movendo;
bool preso;

Fantasma(double, double);
~Fantasma(void);
void Move();
void Status(void);
void Persegue(double, double, bool *);
bool Pega(double, double);
void Recomeca(void);
void Vulneravel(void);
void Desenha(void);
};

#endif // ifndef _FANTASMA_H_
