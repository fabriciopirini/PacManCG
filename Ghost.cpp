//code by John Hollister 2005

#include "Ghost.h"
#include "Board.h"
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


// Destructor
Ghost::~Ghost(void){}

//Constructor
Ghost::Ghost(double tx, double ty)
{
	tx = x;
	ty = y;
	angle = 90;
	max_speed = speed = 0.1;
	color[0] = 1;
	color[1] = 0;
	color[2] = 0;

	eaten = false;

	edible_max_time = 400;
	edible = false;
	in_jail = true;
	jail_timer = 66;
}


void
Ghost::Reinit(void)
{
	//reset some vars
	edible = false;
	in_jail = true;
	angle = 90;
}

//move ghost in the direction it's facing
void
Ghost::Move()
{
	x +=  speed*cos(M_PI/180*angle);
	y +=  speed*sin(M_PI/180*angle);
}


void
Ghost::Update(void)
{
	//TRANSPORT
	if ((int)x == 0 && (int) y == 14 && (!(transporting)))
	{
		angle=180;
	}
	if (x < 0.1 && (int) y == 14)
	{
		x = 26.9;
		transporting = true;
	}

	if ((int)x == 27 && (int) y == 14 && (!(transporting)))
	{
		angle=0;
	}
	if (x > 26.9 && (int) y == 14)
	{
		x = 0.1;
		transporting = true;
	}
	if ((int)x == 2 || (int)x == 25)
		transporting = false;

	if (((int) x < 5 || (int) x > 21) && (int) y == 14 && !edible && !eaten)
		speed = max_speed/2;
	else if (!edible && !eaten)
		speed = max_speed;

	//edibility
	if (edible_timer == 0 && edible && !eaten)
	{
		edible = false;
		speed = max_speed;
	}

	if (edible)
		edible_timer--;

	//JAIL
	if (in_jail && (int) (y+0.9) == 11)
	{
		in_jail = false;
		angle = 180;
	}

	if (in_jail && ((int)x == 13 || (int)x == 14))
	{
		angle = 270;
	}

	//if time in jail is up, position for exit
	if (jail_timer == 0  && in_jail)
	{
		//move right to exit
		if (x < 13)
			angle = 0;
		if (x > 14)
			angle = 180;
	}

	//decrement time in jail counter
	if (jail_timer > 0)
		jail_timer--;

	//EATEN GHOST SEND TO JAIL
	if (eaten && ((int) x == 13 || (int) (x+0.9) == 14) && ((int)y > 10 && (int) y < 15))
	{
		in_jail = true;
		angle = 90;
		if((int) y == 14)
		{
			eaten = false;
			speed = max_speed;
			jail_timer = 66;
			x = 11;
		}
	}
}


bool
Ghost::Catch(double px, double py)
{
	//0.4 by 0.4 unit box for collision detection
	if (px - x < 0.2 && px - x > -0.2 && py - y < 0.2 && py - y > -0.2)
	{
		return true;
	}
	return false;
}


//called when pacman eats a big pebble
void
Ghost::Vulnerable(void)
{
	if (!(edible))
	{
		angle = ((int)angle + 180)%360;
		speed = max_speed/2;
	}
	edible = true;
	edible_timer = edible_max_time;
}




//hunt down pacman given his coordinates
void
Ghost::Chase(double px, double py, bool *open_move)
{

	//this will make the ghost run if it's edible
	int c;
	if (edible)
		c = -1;
	else
		c = 1;

	bool moved = false;
	//test change of direction first by 90 or -90 degrees
	//change to y direction
	if ((int) angle == 0 || (int) angle == 180)
	{
		if ((int)c*py > (int)c*y && open_move[1])
			angle = 90;

		else if ((int)c*py < (int)c*y && open_move[3])
			angle = 270;
	} else if ((int) angle == 90 || (int) angle == 270)
	{
		if ((int)c*px > (int)c*x && open_move[0])
			angle = 0;
		else if ((int)c*px < (int)c*x && open_move[2])
			angle = 180;
	}

	//maybe randomize!

	if ((int) angle == 0 && !open_move[0])
		angle = 90;
	if ((int) angle == 90 && !open_move[1])
		angle = 180;
	if ((int) angle == 180 && !open_move[2])
		angle = 270;
	if ((int) angle == 270 && !open_move[3])
		angle = 0;
	if ((int) angle == 0 && !open_move[0])
		angle = 90;

}

void
Ghost::Draw(void)
{
	if (!edible)
		glColor3f(color[0],color[1],color[2]);
	else
	{
		if (edible_timer < 150)
			glColor3f((edible_timer/10)%2,(edible_timer/10)%2,1);
		if (edible_timer >= 150)
			glColor3f(0,0,1);
	}
	if (eaten)
		glColor3f(0,0,0);

	glPushMatrix();
	glTranslatef(x,-y,0);
	glTranslatef(.5,0.6,0);
	glTranslatef((float)Board::BOARD_X/-2.0f, (float) Board::BOARD_Y/2.0f,0.5);
	glutSolidSphere(.5,10,10);
	glPopMatrix();

}
