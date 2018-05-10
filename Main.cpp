// Bibliotecas
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

// Headers
#include "Camera.h"
#include "Fantasma.h"
#include "Mapa.h"
#include "Pacman.h"

int lastKey, freeze_timer, num_fantasmas = 4, h, w, f_inicio[4] = {11, 12, 15, 16};
float razao;
bool gameover = false;

void init(void);
Camera *camera;
Mapa   *mapa;
Pacman *pacman;
Fantasma *fantasma[4];

// Desenha o jogo
void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a câmera para a posição inicial do Pacman
	camera->Posicao(pacman->x, pacman->y, pacman->angulo);

	// Transporta o Pacman pelas laterais
	if ((int)pacman->x == 27 && (int)pacman->y == 14 && pacman->angulo == 0) {
		pacman->x     = 0;
		pacman->mover = true;
	}
	else if ((int)(pacman->x + 0.9) == 0 && (int)pacman->y == 14 && pacman->angulo == 180) {
		pacman->x     = 27;
		pacman->mover = true;
	}

	// Verifica se o Pacman pode andar
	if (pacman->mover) {
		pacman->Move();
	}

	// Verifica se o caminho andado pelo Pacman é válido, se não for, colidir
	if (!(mapa->NaTela((int)(pacman->x + cos(M_PI / 180 * pacman->angulo)), (int)(pacman->y + sin(M_PI / 180 * pacman->angulo)))) && (pacman->x - (int)pacman->x < 0.1) &&(pacman->y - (int)pacman->y < 0.1)) {
		pacman->mover = false;
	}

	// Define a ação de "comer" os pontos
	if (mapa->pontos[(int)(pacman->y + 0.5)][(int)(pacman->x + 0.5)] == 1) {
		mapa->pontos[(int)(pacman->y + 0.5)][(int)(pacman->x + 0.5)] = 0;
		mapa->pontosRest--;
		// std::cout << "Ponto comido: (" << pacman->y << ", " << pacman->x << ")\n";
	}
	else if(mapa->pontos[(int)(pacman->y + 0.5)][(int)(pacman->x + 0.5)] == 3) {
		mapa->pontos[(int)(pacman->y + 0.5)][(int)(pacman->x + 0.5)] = 0;
		mapa->pontosRest--;

		for (int i = 0; i < 4; i++)
		{
			if (!fantasma[i]->pego) {
				fantasma[i]->Vulneravel();
			}
		}
	}

	// Todos os pontos foram "comidos"
	if (mapa->pontosRest == 0) {
		pacman->vidas = 3;
		init();
		mapa->Recomeca();
	}

	mapa->Desenha();

	if (!gameover) {
		pacman->Desenha();
	}

	for (int i = 0; i < num_fantasmas; i++)
	{
		// Movimento dos fantasmas
		if (!gameover && freeze_timer == 0) {
			fantasma[i]->Status();
		}

		if (!fantasma[i]->preso && fantasma[i]->x-(int)fantasma[i]->x<0.1 && fantasma[i]->y-(int)fantasma[i]->y<0.1) {
			bool movimento[4];

			// Verifica os movimentos possíveis
			for (int ang = 0; ang < 4; ang++) {
				movimento[ang] = mapa->NaTela((int)(fantasma[i]->x + cos(M_PI / 180 * ang * 90)), (int)(fantasma[i]->y + sin(M_PI / 180 * ang * 90)));
			}

			// Verifica a posição do Pacman
			if (!fantasma[i]->pego) {
				if (fantasma[i]->x-(int)fantasma[i]->x<0.1 && fantasma[i]->y-(int)fantasma[i]->y<0.1) {
					fantasma[i]->Persegue(pacman->x, pacman->y, movimento);
				}
			}
			else{
				if (fantasma[i]->x-(int)fantasma[i]->x<0.1 && fantasma[i]->y-(int)fantasma[i]->y<0.1) {
					fantasma[i]->Persegue(13, 11, movimento);
				}
			}
		}

		if (fantasma[i]->preso && !(mapa->NaTela((int)(fantasma[i]->x + cos(M_PI / 180 * fantasma[i]->angulo)), (int)(fantasma[i]->y + sin(M_PI / 180 * fantasma[i]->angulo)))) && fantasma[i]->tempo_preso > 0 && fantasma[i]->x - (int)fantasma[i]->x < 0.1 && fantasma[i]->y - (int)fantasma[i]->y < 0.1) {
			fantasma[i]->angulo = (double)(((int)fantasma[i]->angulo + 180) % 360);
		}

		if (!gameover && freeze_timer == 0) {
			fantasma[i]->Move();
		}

		fantasma[i]->Desenha();

		if (!(fantasma[i]->pego)) {
			bool colisao = fantasma[i]->Pega(pacman->x, pacman->y);
			// Se o Pacman foi pego
			if (colisao && !(fantasma[i]->vulneravel)) {
				pacman->vidas--;
				if (pacman->vidas == 0) {
					gameover = true;
				}
				else{
					init();
				}
				i = 4;
			}
			// Se o fantasma foi pego
			else if (colisao && (fantasma[i]->vulneravel)) {
				// Reseta as variáveis
				fantasma[i]->vulneravel = false;
				fantasma[i]->pego = true;
				fantasma[i]->velocidade = 0.1;
			}
		}
	}
	glutSwapBuffers();
}

void TimerFunction(int valor) {
	// Tempo inicial para iniciar o jogo
	if (freeze_timer > 0) {
		freeze_timer--;
	}

	// Se o jogo está sendo executado
	if (freeze_timer == 0) {
		// Seta para direita
		if ((lastKey == GLUT_KEY_RIGHT) && ((int)pacman->y - pacman->y > -0.1) && (pacman->angulo != 0)) {
			if (mapa->NaTela(pacman->x + 1, pacman->y)) {
				pacman->mover  = true;
				pacman->angulo = 0;
			}
		}

		// Seta para esquerda
		else if ((lastKey == GLUT_KEY_LEFT) && ((int)pacman->y - pacman->y > -0.1) && (pacman->angulo != 180)) {
			if (mapa->NaTela(pacman->x - 1, pacman->y)) {
				pacman->mover  = true;
				pacman->angulo = 180;
			}
		}

		// Seta para cima
		if ((lastKey == GLUT_KEY_UP) && ((int)pacman->x - pacman->x > -0.1) && (pacman->angulo != 270)) {
			if (mapa->NaTela(pacman->x, pacman->y - 1)) {
				pacman->mover  = true;
				pacman->angulo = 270;
			}
		}

		// Seta para baixo
		else if ((lastKey == GLUT_KEY_DOWN) && ((int)pacman->x - pacman->x > -0.1) && (pacman->angulo != 90)) {
			if (mapa->NaTela(pacman->x, pacman->y + 1)) {
				pacman->mover  = true;
				pacman->angulo = 90;
			}
		}
	}

	if(gameover) {
		pacman->vidas = 3;
		init();
		mapa->Recomeca();
		gameover = false;
	}

	// Finaliza
	glutPostRedisplay();
	glutTimerFunc(20, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0) {
		h = 1;
	}

	razao = 1.0f * w / (h);
	glViewport(0, 0, w, h);
	camera = new Camera(razao);
}

// Configura o jogo
void init(void) {
	// Congela o Pacman por 1 segundo no inicio do jogo
	freeze_timer = 50;
	pacman->Recomeca();

	// Coloca os fantasmas em suas posições iniciais
	float f_cores[4][3] = {{255, 0, 0}, {120, 240, 120}, {255, 200, 200}, {255, 125, 0}};

	for (int i = 0; i < num_fantasmas; i++)
	{
		fantasma[i]->Recomeca();
		fantasma[i]->x              = f_inicio[i];
		fantasma[i]->y              = 14;
		fantasma[i]->pego           = false;
		fantasma[i]->tempo_preso    = i * 33 + 66;
		fantasma[i]->velocidade_max = 0.1 - 0.01 * (float)i;
		fantasma[i]->velocidade     = fantasma[i]->velocidade_max;

		// Colore os fantasmas
		for (int j = 0; j < 3; j++)
		{
			fantasma[i]->cor[j] = f_cores[i][j] / 255.0f;
		}
	}
}

void catchKey(int key, int x, int y) {
	lastKey = key;
	if(lastKey == 1) {
		//glutDestroyWindow();
		exit(1);
	}
}

void menu() {
	printf("\033c");
	printf("\x1b[92m\e[1mBEM VINDO AO JOGO DO PACMAN!\e[0m\x1b[0m\n");
	printf("Para \e[1mcontrolar o Pac-man\e[0m, utilize as \e[1mSETAS DIRECIONAS!\e[0m\n");
	printf("Para \e[1mfechar\e[0m o jogo, pressione \e[1mF1\e[0m\n");
	printf("Para \e[1miniciar\e[0m o jogo, \e[1mpressione ENTER\e[0m-> ");

	while (std::cin.get() != '\n') {}
}

int main(int argc, char *argv[]) {
	menu();
	//system("mpg123 Overworld.mp3 &");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Configurações gerais
	glutInitWindowSize(800, 640);
	glutInitWindowPosition(500, 150);
	glutCreateWindow("PacMan GLUT 3D");

	// Faz o mouse ficar invisível
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(catchKey);
	glutTimerFunc(20, TimerFunction, 1);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	// Exibe o mapa
	mapa = new Mapa();

	// Exibe o Pacman na sua posição inicial
	pacman = new Pacman(0, 0);

	// Exibe os fantasmas em suas posições iniciais
	for (int i = 0; i < num_fantasmas; i++)
		fantasma[i] = new Fantasma(f_inicio[i], 14);

	init();
	glutMainLoop();
	//system("ps -ef | grep mpg123 | awk '{print $2}' | xargs kill -9 &");
	return 0;
}
