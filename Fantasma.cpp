// Bibliotecas
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Headers
#include "Fantasma.h"
#include "Mapa.h"

// Coordenadas, ângulos e medidas
GLfloat f_alfa, f_beta;
GLfloat f_raio     = 0.5;
GLfloat fx, fy, fz = 0;
int f_triangulos   = 20;

// Construtor
Fantasma::Fantasma(double tx, double ty) {
	tx             = x;
	ty             = 14;
	angulo         = 90;
	cor[0]         = 1;
	cor[1]         = 0;
	cor[2]         = 0;
	velocidade_max = velocidade = 0.1;
	pego                = false;
	tempoMax_vulneravel = 400;
	vulneravel          = false;
	preso               = true;
	tempo_preso         = 66;
}

// Destrutor
Fantasma::~Fantasma(void) {
}

// Reseta as variáveis
void Fantasma::Recomeca(void) {
	vulneravel = false;
	preso      = true;
	angulo     = 90;
}

// Move o fantasma na direção que estiver olhando
void Fantasma::Move() {
	x += velocidade * cos(M_PI / 180 * angulo);
	y += velocidade * sin(M_PI / 180 * angulo);
}

void Fantasma::Status(void) {
	// Movimentação
	if (((int)x == 0) && ((int)y == 14) && (!(movendo))) {
		angulo = 180;
	}

	if ((x < 0.1) && ((int)y == 14)) {
		x       = 26.9;
		movendo = true;
	}

	if (((int)x == 27) && ((int)y == 14) && (!(movendo))) {
		angulo = 0;
	}

	if ((x > 26.9) && ((int)y == 14)) {
		x       = 0.1;
		movendo = true;
	}

	if (((int)x == 2) || ((int)x == 25)) {
		movendo = false;
	}

	if ((((int)x < 5) || ((int)x > 21)) && ((int)y == 14) && !vulneravel && !pego) {
		velocidade = velocidade_max / 2;
	}
	else if (!vulneravel && !pego) {
		velocidade = velocidade_max;
	}

	// Vulnerabilidade
	if ((tempo_vulneravel == 0) && vulneravel && !pego) {
		vulneravel = false;
		velocidade = velocidade_max;
	}

	if (vulneravel) {
		tempo_vulneravel--;
	}

	// Preso
	if (preso && ((int)(y + 0.9) == 11)) {
		preso  = false;
		angulo = 180;
	}

	if (preso && (((int)x == 13) || ((int)x == 14))) {
		angulo = 270;
	}

	// Se o tempo preso chegar no limite, o fantasma é solto
	if ((tempo_preso == 0) && preso) {
		// O fantasma se move pra saída
		if (x < 13) {
			angulo = 0;
		}

		if (x > 14) {
			angulo = 180;
		}
	}

	// Decrementa o timer na prisão
	if (tempo_preso > 0) {
		tempo_preso--;
	}

	// O fantasma pego é enviado para a prisão
	if (pego && (((int)x == 13) || ((int)(x + 0.9) == 14)) &&
	    (((int)y > 10) && ((int)y < 15))) {
		preso  = true;
		angulo = 90;

		if ((int)y == 14) {
			pego        = false;
			velocidade  = velocidade_max;
			tempo_preso = 66;
			x           = 11;
		}
	}
}

// Colisão do fantasma com o Pacman
bool Fantasma::Pega(double px, double py) {
	// Colisão de 0.4 x 0.4
	if ((px - x < 0.2) && (px - x > -0.2) && (py - y < 0.2) && (py - y > -0.2)) {
		return true;
	}
	return false;
}

// Chamada quando o Pacman come um ponto energizado
void Fantasma::Vulneravel(void) {
	if (!(vulneravel)) {
		angulo     = ((int)angulo + 180) % 360;
		velocidade = velocidade_max / 2;
	}
	vulneravel       = true;
	tempo_vulneravel = tempoMax_vulneravel;
}

// Busca o Pacman a partir de suas coordenadas
void Fantasma::Persegue(double px, double py, bool *movimento) {
	// Essa variável faz com que o fantasma corra caso esteja vulnerável
	int c;

	if (vulneravel) {
		c = -1;
	}
	else{
		c = 1;
	}

	if (((int)angulo == 0) || ((int)angulo == 180)) {
		if (((int)c * py > (int)c * y) && movimento[1]) {
			angulo = 90;
		}
		else if (((int)c * py < (int)c * y) && movimento[3]) {
			angulo = 270;
		}
	}
	else if (((int)angulo == 90) || ((int)angulo == 270)) {
		if (((int)c * px > (int)c * x) && movimento[0]) {
			angulo = 0;
		}
		else if (((int)c * px < (int)c * x) && movimento[2]) {
			angulo = 180;
		}
	}

	// É possível deixar aleatório
	if (((int)angulo == 0) && !movimento[0]) {
		angulo = 90;
	}

	if (((int)angulo == 90) && !movimento[1]) {
		angulo = 180;
	}

	if (((int)angulo == 180) && !movimento[2]) {
		angulo = 270;
	}

	if (((int)angulo == 270) && !movimento[3]) {
		angulo = 0;
	}

	if (((int)angulo == 0) && !movimento[0]) {
		angulo = 90;
	}
}

// Desenha os fantasmas
void Fantasma::Desenha(void) {
	if (!vulneravel) {
		glColor3f(cor[0], cor[1], cor[2]);
	}
	else{
		if (tempo_vulneravel < 150) {
			glColor3f((tempo_vulneravel / 10) % 2, (tempo_vulneravel / 10) % 2, 1);
		}

		else {
			glColor3f(0, 0, 1);
		}
	}

	if (pego) {
		glColor3f(0, 0, 0);
	}

	glPushMatrix();
	glTranslatef(x, -y, 0);
	glTranslatef(.5, 0.6, 0);
	glTranslatef((float)Mapa::MAPA_X / -2.0f, (float)Mapa::MAPA_Y / 2.0f, 0.5);

	for (f_alfa = 0.0; f_alfa < M_PI; f_alfa += M_PI / f_triangulos)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for (f_beta = 0.0; f_beta < 2.01 * M_PI; f_beta += M_PI / f_triangulos)
		{
			fx = f_raio * cos(f_beta) * sin(f_alfa);
			fy = f_raio * sin(f_beta) * sin(f_alfa);
			fz = f_raio * cos(f_alfa);
			glVertex3f(fx, fy, fz);

			fx = f_raio * cos(f_beta) * sin(f_alfa + M_PI / f_triangulos);
			fy = f_raio * sin(f_beta) * sin(f_alfa + M_PI / f_triangulos);
			fz = f_raio * cos(f_alfa + M_PI / f_triangulos);
			glVertex3f(fx, fy, fz);
		}
		glEnd();
	}
	glPopMatrix();
}
