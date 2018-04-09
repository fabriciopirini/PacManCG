#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include "Camera.h"
#include "Mapa.h"
#include "Pacman.h"

static int   lastKey;
static int   start_timer;
static float ratio;
static int   h, w;
static bool  gameover = false;

void init(void);
Camera *camera;
Mapa   *mapa;
Pacman *pacman;

// Tipos de visão do mapa
int view;

void RenderScene() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Define a câmera para a posição inicial do Pacman
  camera->Posicao(pacman->x, pacman->y, pacman->angulo, view);

  // Transporta o Pacman pelas laterais
  if (((int)pacman->x == 27) && ((int)pacman->y == 14) && (pacman->angulo == 0)) {
    pacman->x        = 0;
    pacman->animacao = true;
  }
  else if (((int)(pacman->x + 0.9) == 0) && ((int)pacman->y == 14) &&
           (pacman->angulo == 180)) {
    pacman->x        = 27;
    pacman->animacao = true;
  }

  // Verifica a possibilidade das animações
  if (pacman->animacao) pacman->Move();

  if (!(mapa->NaTela((int)(pacman->x + cos(M_PI / 180 * pacman->angulo)),
                     (int)(pacman->y + sin(M_PI / 180 * pacman->angulo)))) &&
      (pacman->x - (int)pacman->x < 0.1) &&
      (pacman->y - (int)pacman->y < 0.1)) pacman->animacao = false;

  mapa->Desenha();

  if (!gameover) pacman->Desenha();

  glutSwapBuffers();
}

void TimerFunction(int valor) {
  // Tempo inicial para iniciar o jogo
  if (start_timer > 0) start_timer--;

  // Se o jogo está sendo executado
  if (!gameover && (start_timer == 0)) {
    // Seta para direita
    if ((lastKey == GLUT_KEY_RIGHT) && ((int)pacman->y - pacman->y > -0.1) &&
        (pacman->angulo != 0)) {
      if (mapa->NaTela(pacman->x + 1, pacman->y)) {
        pacman->animacao = true;
        pacman->angulo   = 0;
      }
    }

    // Seta para esquerda
    else if ((lastKey == GLUT_KEY_LEFT) && ((int)pacman->y - pacman->y > -0.1) &&
             (pacman->angulo != 180)) {
      if (mapa->NaTela(pacman->x - 1, pacman->y)) {
        pacman->animacao = true;
        pacman->angulo   = 180;
      }
    }

    // Seta para cima
    if ((lastKey == GLUT_KEY_UP) && ((int)pacman->x - pacman->x > -0.1) &&
        (pacman->angulo != 270)) {
      if (mapa->NaTela(pacman->x, pacman->y - 1)) {
        pacman->animacao = true;
        pacman->angulo   = 270;
      }
    }

    // Seta para baixo
    else if ((lastKey == GLUT_KEY_DOWN) && ((int)pacman->x - pacman->x > -0.1) &&
             (pacman->angulo != 90)) {
      if (mapa->NaTela(pacman->x, pacman->y + 1)) {
        pacman->animacao = true;
        pacman->angulo   = 90;
      }
    }
  }

  // Inicia um novo jogo
  if ((lastKey == 13) && gameover) {
    pacman->vidas = 3;
    init();
    gameover = false;
  }

  // Finaliza
  glutPostRedisplay();

  glutTimerFunc(20, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h) {
  if (h == 0) h = 1;

  ratio = 1.0f * w / (h);
  glViewport(0, 0, w, h);
  camera = new Camera(ratio);
}

// Configura o jogo
void init(void) {
  start_timer = 100;
  pacman->Recomeca();
}

void catchKey(int key, int x, int y) {
  lastKey = key;
}

void menu() {
  printf("\033c");
  printf("BEM VINDO AO JOGO DO PACMAN!\n");
  printf("PARA INICIAR O JOGO, PRESSIONE ENTER: ");

  while (std::cin.get() != '\n') {}
}

int main(int argc, char *argv[]) {
  menu();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  // Configurações gerais
  glutInitWindowSize(800, 640);
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
  int start_x[4] = { 11, 12, 15, 16 };
  pacman = new Pacman(13.5, 23);

  init();

  glutMainLoop();

  return 0;
}
