#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "Camera.h"
#include "Board.h"
#include "Pac.h"

static int lastKey;

int start_timer;

void init(void);

//window info
float ratio;
int h,w;

//camera object
Camera *camera;

//viewing positions
int view;
//stops key repeats
int v_timer;

//playing board
Board *board;

//Mr. Pacman
Pac *pacman;

bool gameover = false;	// used to tell if the game has ended

// draw the scene
void RenderScene() {
    //camera update
    camera->Set_position(pacman->x, pacman->y, pacman->angle, view);

    //pipe transport
    if ((int)pacman->x == 27 && (int) pacman->y == 14 && pacman->angle == 0) {
        pacman->x = 0;
        pacman->animate = true;
    } else if ((int)(pacman->x + 0.9) == 0 && (int) pacman->y == 14 && pacman->angle == 180) {
        pacman->x = 27;
        pacman->animate = true;
    }

    //do animation/movement checks for pacman
    if (pacman->animate)
        pacman->Move();
    if(!(board->IsOpen((int)(pacman->x + cos(M_PI/180*pacman->angle)),
                       (int)(pacman->y + sin(M_PI/180*pacman->angle)))) &&
                        pacman->x-(int)pacman->x < 0.1 && pacman->y-(int)pacman->y < 0.1)
        pacman->animate = false;

    /*//do pebble eating
    if (board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)]	== 1) {
        board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)]	= 0;
        board->pebbles_left--;
    } else if(board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)] == 3) {
        board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)]	= 0;
        board->pebbles_left--;
    }

    //board is cleared of pebbles
    if (board->pebbles_left == 0) {
        init();
        board->tp_restore();
    }*/

    board->Draw();
    if (!gameover)
        pacman->Draw();

    glutSwapBuffers();
}


void TimerFunction(int value) {
    //short pause when starting game
    if (start_timer > 0)
        start_timer--;

    //make sure game is in play
    if (!gameover && start_timer == 0) {
        // Get keyboard input
        //move right
        if(lastKey == GLUT_KEY_RIGHT && (int) pacman->y - pacman->y > -0.1 && pacman->angle != 0) {
            if (board->IsOpen(pacman->x+1, pacman->y)) {
                pacman->animate = true;
                pacman->angle = 0;
            }
        } else
            //move left
            if(lastKey == GLUT_KEY_LEFT && (int) pacman->y - pacman->y > -0.1 && pacman->angle != 180) {
                if (board->IsOpen(pacman->x-1, pacman->y)) {
                    pacman->animate = true;
                    pacman->angle = 180;
                }
            }
        //move up
        if(lastKey == GLUT_KEY_UP && (int) pacman->x - pacman->x > -0.1 && pacman->angle != 270) {
            if (board->IsOpen(pacman->x, pacman->y - 1)) {
                pacman->animate = true;
                pacman->angle = 270;
            }
        } else
            //move down
            if(lastKey == GLUT_KEY_DOWN && (int) pacman->x - pacman->x > -0.1 && pacman->angle != 90) {
                if (board->IsOpen(pacman->x, pacman->y + 1)) {
                    pacman->animate = true;
                    pacman->angle = 90;
                }
            }
    }

    //start a new game
    if (lastKey == 13 && gameover) {
        pacman->lives = 3;
        init();
        //board->tp_restore();
        gameover = false;
    }
    //quit
    glutPostRedisplay();

    glutTimerFunc(20, TimerFunction, 1);
}


void ChangeSize(GLsizei w, GLsizei h) {
    if(h == 0)
        h = 1;

    ratio = 1.0f * w / (h);
    glViewport(0,0,w,h);
    camera = new Camera(ratio);

}

//SET UP THE GAME
void init(void) {
    start_timer = 140;
    pacman->Reinit();
}

void catchKey(int key, int x, int y) {
    lastKey = key;
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

    //windowed mode
    glutInitWindowSize(600, 500);
    glutCreateWindow("Pac GL 3D");

    //fullscreen mode
    //glutGameModeString( "800x600:16@60" );
    //glutEnterGameMode();

    //make mouse disappear
    glutSetCursor(GLUT_CURSOR_NONE);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(catchKey);
    glutTimerFunc(20, TimerFunction, 1);

    //draw the level...
    glClearColor(.3, .3, .3, 1.0f);

    //set up board
    board = new Board();
    int start_x[4] = {11,12,15,16};
    pacman = new Pac(13.5,23);

    init();

    //initial view is the "3D" view
    view = 0;
    v_timer = 0;

    glutMainLoop();

    return 0;
}
