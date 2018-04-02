//code by John Hollister 2005

#include "Camera.h"
#include "Board.h"
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


// Destructor
Camera::~Camera(void){}

//Constructor
Camera::Camera(float ratio)
{
	//Cull back faces
	glEnable(GL_CULL_FACE);

    double  eye[3];
    float   color[4], dir[4];

	// Enable lighting with one light.
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// Ambient and diffuse lighting track the current color.
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Turn on normal vector normalization. You don't have to give unit
	// normal vector, and you can scale objects.
	glEnable(GL_NORMALIZE);

	// Do some light stuff. Diffuse color, and zero specular color
	// turns off specular lighting.
	color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	color[0] = 0.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_SPECULAR, color);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the clipping volume
	gluPerspective(60,ratio,0.005,100);

	// Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    // Position the light source. This has to happen after the viewing
    // transformation is set up, so that the light stays fixed in world
    // space. This is a directional light - note the 0 in the w component.
    dir[0] = 0.0; dir[1] = 1.0; dir[2] = 1.0; dir[3] = 0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, dir);
}

void
Camera::Set_position(float x_at, float y_at, double angle, int view)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//if (view == 1)
		gluLookAt(-1.5, -26, 20, -1.5, -9, 1, 0.0f,0.0f,1.0f);
	/*else
		gluLookAt(.8f*(float)(x_at - Board::BOARD_X/2)-0.3, -y_at+Board::BOARD_Y/4-10, 20,
			x_at - Board::BOARD_X/2, -y_at+Board::BOARD_Y/2, 1, 0.0f,0.0f,1.0f);
        printf("%f", .8f*(float)(x_at - Board::BOARD_X/2)-0.3);
        printf("%f", -y_at+Board::BOARD_Y/4-10);
        printf("%f", x_at - Board::BOARD_X/2);
        printf("%f", -y_at+Board::BOARD_Y/2);
        printf("\n");*/

}
