#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include "Camera.h"
#include "Mapa.h"
#include "Pacman.h"

static int   lastKey;
static int   freeze_timer;
static float razao;
static int   h, w;

void init(void);
Camera *camera;
Mapa   *mapa;
Pacman *pacman;

void RenderScene() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Define a câmera para a posição inicial do Pacman
  camera->Posicao(pacman->x, pacman->y, pacman->angulo);

  // Transporta o Pacman pelas laterais
  if (((int)pacman->x == 27) && ((int)pacman->y == 14) && (pacman->angulo == 0)) {
    pacman->x        = 0;
    pacman->mover = true;
  }
  else if (((int)(pacman->x + 0.9) == 0) && ((int)pacman->y == 14) &&
           (pacman->angulo == 180)) {
    pacman->x        = 27;
    pacman->mover = true;
  }

  // Verifica a possibilidade das animações
  if (pacman->mover) 
    pacman->Move();

  // Verifica se o caminho andado pelo Pacman é válido, se não for, colidir
  if (!(mapa->NaTela((int)(pacman->x + cos(M_PI / 180 * pacman->angulo)), (int)(pacman->y + sin(M_PI / 180 * pacman->angulo)))) && 
      (pacman->x - (int)pacman->x < 0.1) &&
      (pacman->y - (int)pacman->y < 0.1)) 
    pacman->mover = false;

  mapa->Desenha();

  pacman->Desenha();

  glutSwapBuffers();
}

void TimerFunction(int valor) {
  // Tempo inicial para iniciar o jogo
  if (freeze_timer > 0) freeze_timer--;

  // Se o jogo está sendo executado
  if (freeze_timer == 0) {
    // Seta para direita
    if ((lastKey == GLUT_KEY_RIGHT) && ((int)pacman->y - pacman->y > -0.1) &&
        (pacman->angulo != 0)) {
      if (mapa->NaTela(pacman->x + 1, pacman->y)) {
        pacman->mover = true;
        pacman->angulo   = 0;
      }
    }

    // Seta para esquerda
    else if ((lastKey == GLUT_KEY_LEFT) && ((int)pacman->y - pacman->y > -0.1) &&
             (pacman->angulo != 180)) {
      if (mapa->NaTela(pacman->x - 1, pacman->y)) {
        pacman->mover = true;
        pacman->angulo   = 180;
      }
    }

    // Seta para cima
    if ((lastKey == GLUT_KEY_UP) && ((int)pacman->x - pacman->x > -0.1) &&
        (pacman->angulo != 270)) {
      if (mapa->NaTela(pacman->x, pacman->y - 1)) {
        pacman->mover = true;
        pacman->angulo   = 270;
      }
    }

    // Seta para baixo
    else if ((lastKey == GLUT_KEY_DOWN) && ((int)pacman->x - pacman->x > -0.1) &&
             (pacman->angulo != 90)) {
      if (mapa->NaTela(pacman->x, pacman->y + 1)) {
        pacman->mover = true;
        pacman->angulo   = 90;
      }
    }
  }

  // Finaliza
  glutPostRedisplay();

  glutTimerFunc(20, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h) {
  if (h == 0) h = 1;

  razao = 1.0f * w / (h);
  glViewport(0, 0, w, h);
  camera = new Camera(razao);
}

// Configura o jogo
void init(void) {
  // Congela o Pacman por 1 segundo no inicio do jogo
  freeze_timer = 50; 
  pacman->Recomeca();
}

void catchKey(int key, int x, int y) {
  lastKey = key;
  //printf("%d\n", key);
  if(lastKey == 1){
      exit(0);
      //system("ps -ef | grep mpg123 | awk '{print $2}' | xargs kill -9 &");
  }
}

void menu() {
  printf("\033c");
  printf("BEM VINDO AO JOGO DO PACMAN!\n");
  printf("PARA INICIAR O JOGO, PRESSIONE ENTER: ");

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

  init();

  glutMainLoop();
  //system("ps -ef | grep mpg123 | awk '{print $2}' | xargs kill -9 &");
  return 0;
}
