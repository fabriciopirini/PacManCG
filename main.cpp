#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <ncurses.h>
#include "Camera.h"
#include "Board.h"
#include "Pac.h"
#include "Ghost.h"

static int lastKey;
//delays in game
int start_timer;

void init(void);

//number of ghosts on the board
int num_ghosts = 4;

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

//mr. pacman
Pac *pacman;

//ghosts
Ghost *ghost[4];


bool gameover = false;	// used to tell if the game has ended

// draw the scene
void RenderScene()
{
	//camera update
	camera->Set_position(pacman->x, pacman->y, pacman->angle, view);

	//pipe transport
	if ((int)pacman->x == 27 && (int) pacman->y == 14 && pacman->angle == 0)
	{
		pacman->x = 0;
		pacman->animate = true;
	}else
	if ((int)(pacman->x + 0.9) == 0 && (int) pacman->y == 14 && pacman->angle == 180)
	{
		pacman->x = 27;
		pacman->animate = true;
	}


	//do animation/movement checks for pacman
	if (pacman->animate)
		pacman->Move();
	if(!(board->IsOpen((int)(pacman->x + cos(M_PI/180*pacman->angle)),
			(int)(pacman->y + sin(M_PI/180*pacman->angle)))) &&
			pacman->x - (int)pacman->x < 0.1 && pacman->y - (int)pacman->y < 0.1)
		pacman->animate = false;


	//do pebble eating
	if (board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)]	== 1)
	{
		board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)]	= 0;
		board->pebbles_left--;
	} else if(board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)] == 3)
	{
		board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)]	= 0;
		board->pebbles_left--;
		for (int i = 0; i < 4; i++)
		{
			if (!ghost[i]->eaten)
				ghost[i]->Vulnerable();
		}
	}

	//board is cleared of pebbles
	if (board->pebbles_left == 0)
	{
		init();
		board->tp_restore();
	}



	board->Draw();
	if (!gameover)
		pacman->Draw();


	for (int a = 0; a < num_ghosts; a++)
	{

		//GHOST DRAWING/MOVING
		if (!gameover && start_timer == 0)
			ghost[a]->Update();

		if (!ghost[a]->in_jail &&
			ghost[a]->x - (int)ghost[a]->x < 0.1 && ghost[a]->y - (int)ghost[a]->y < 0.1)
		{

			bool open_move[4];
			//find available moves
			for (int ang = 0; ang < 4; ang++)
			{
				open_move[ang] = board->IsOpen((int)(ghost[a]->x + cos(M_PI/180*ang*90)),
					(int)(ghost[a]->y + sin(M_PI/180*ang*90)));
			}

            //TRACK PACMANS MOVEMENT
			if (!ghost[a]->eaten)
			{
				if(ghost[a]->x - (int)ghost[a]->x < 0.1 && ghost[a]->y - (int)ghost[a]->y < 0.1)
					ghost[a]->Chase(pacman->x, pacman->y, open_move);
			} else {
				if(ghost[a]->x - (int)ghost[a]->x < 0.1 && ghost[a]->y - (int)ghost[a]->y < 0.1)
					ghost[a]->Chase(13, 11, open_move);
			}
		}
		if (ghost[a]->in_jail && !(board->IsOpen((int)(ghost[a]->x + cos(M_PI/180*ghost[a]->angle)),
			(int)(ghost[a]->y + sin(M_PI/180*ghost[a]->angle)))) && ghost[a]->jail_timer > 0 &&
			ghost[a]->x - (int)ghost[a]->x < 0.1 && ghost[a]->y - (int)ghost[a]->y < 0.1)
		{
			ghost[a]->angle = (double)(((int)ghost[a]->angle + 180)%360);
		}

		if (!gameover && start_timer == 0)
			ghost[a]->Move();

		ghost[a]->Draw();

		if(!(ghost[a]->eaten))
		{
			bool collide = ghost[a]->Catch(pacman->x, pacman->y);
			if (collide && !(ghost[a]->edible))  //pacman is eaten
			{
				pacman->lives--;
				if (pacman->lives == 0)
					gameover = true;
				else
					init();
				//break loop
				a = 4;
			}else
			if (collide && ((ghost[a]->edible)))	//ate a ghost send it to jail
			{
				//reset info
				ghost[a]->edible = false;
				ghost[a]->eaten = true;
				ghost[a]->speed = 0.1;
			}
		}

	}
	glutSwapBuffers();
}


void TimerFunction(int value)
{
	//switch views from 3D to classic
	/*if(v_timer == 0)
	{
		view = (view+1)%2;
		v_timer = 10;
	}
	if (v_timer > 0)
		v_timer--;*/

	//short pause when starting game
	if (start_timer > 0)
		start_timer--;

	//make sure game is in play
	if (!gameover && start_timer == 0)
	{
		// Get keyboard input
		//move right
		if(lastKey == GLUT_KEY_RIGHT && (int) pacman->y - pacman->y > -0.1 && pacman->angle != 0)
		{
			if (board->IsOpen(pacman->x+1, pacman->y))
			{
				pacman->animate = true;
				pacman->angle = 0;
			}
		}else
		//move left
		if(lastKey == GLUT_KEY_LEFT && (int) pacman->y - pacman->y > -0.1 && pacman->angle != 180)
		{
			if (board->IsOpen(pacman->x-1, pacman->y))
			{
				pacman->animate = true;
				pacman->angle = 180;
			}
		}
		//move up
		if(lastKey == GLUT_KEY_UP && (int) pacman->x - pacman->x > -0.1 && pacman->angle != 270)
		{
			if (board->IsOpen(pacman->x, pacman->y - 1))
			{
				pacman->animate = true;
				pacman->angle = 270;
			}
		}else
		//move down
		if(lastKey == GLUT_KEY_DOWN && (int) pacman->x - pacman->x > -0.1 && pacman->angle != 90)
		{
			if (board->IsOpen(pacman->x, pacman->y + 1))
			{
				pacman->animate = true;
				pacman->angle = 90;
			}
		}
	}

	//start a new game
	if (lastKey == 13 && gameover)
	{
		pacman->lives = 3;
		init();
		board->tp_restore();
		gameover = false;
	}
	//quit
	glutPostRedisplay();

	glutTimerFunc(20, TimerFunction, 1);
}


void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / (h);
	glViewport(0,0,w,h);
	camera = new Camera(ratio);

}



//SET UP THE GAME
void init(void)
{

	start_timer = 140;
	pacman->Reinit();

	//ghost initial starting positions
	int start_x[4] = {11,12,15,16};
	float ghost_colors[4][3] = {{255,0,0},{120,240,120},{255,200,200},{255,125,0}};

	for (int i = 0; i < num_ghosts; i++)
	{
		ghost[i]->Reinit();
		ghost[i]->x = start_x[i];
		ghost[i]->y = 14;
		ghost[i]->eaten = false;
		ghost[i]->jail_timer = i*33 + 66;
		ghost[i]->max_speed = 0.1 - 0.01*(float)i;
		ghost[i]->speed = ghost[i]->max_speed;
		//colorize ghosts
		for (int j = 0; j < 3; j++)
			ghost[i]->color[j] = ghost_colors[i][j]/255.0f;
	}
}

void catchKey(int key, int x, int y)
{
    lastKey = key;
}

int main(int argc, char * argv[])
{
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

	//put ghosts in starting positions
	for (int i = 0; i < num_ghosts; i++)
	{
		ghost[i] = new Ghost(start_x[i],14);
	}

	init();

	//initial view is the "3D" view
	view = 0;
	v_timer = 0;

	glutMainLoop();

	return 0;
}
