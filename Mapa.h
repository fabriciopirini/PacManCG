#ifndef _MAPA_H_
#define _MAPA_H_

class Mapa {
public:

GLubyte lista[5];           // Define uma lista para cada parede
static const int MAPA_X;
static const int MAPA_Y;

int pontosRest;                     // Quantos pontos faltam
int pontos[31][28];         // Matriz de pontos para comer

Mapa(void);
~Mapa(void);
void Paredes(void);
void Recomeca(void);
void Desenha(void);
bool NaTela(int, int);
};

#endif // ifndef _MAPA_H_
