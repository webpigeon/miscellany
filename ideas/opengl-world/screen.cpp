#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

extern void render_world(int x, int y, float rotation);

#define VIEWING_ANGLE 138
#define CAM_MOVE_UP 'w'
#define CAM_ROT_CCW '.'
#define CAM_ROT_CW ','
#define CAM_MOVE_DOWN 's'
#define CAM_ZOOM_OUT 'z'

GLfloat lightpos[] = { 5.0, 1.0, 5.0 };
GLfloat ambcolor[] = { 1.0, 1.0, 1.0 };


float teapot_x = 5;
float teapot_z = 5;
float teapot_rotation = 0;

float lx = 0.0f;
float lz = -1.0f;

float cam_height = 1.9;

float deltaAngle = 0.0f;
float deltaHeight = 1.0f;

int xOrigin = -1;
int lastY = -1;

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	//if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.01f;

		// update camera's direction
		lx = sin(teapot_rotation + deltaAngle);
		lz = -cos(teapot_rotation + deltaAngle);
	//}
	
	if (lastY == -1) {
		lastY = y;
	}

	int delta = lastY - y;
	cout << delta << endl;
	if ( delta > 0) {
		cam_height += deltaHeight * 0.01f;
	} else {
		cam_height -= deltaHeight * 0.01f;
	}
	lastY = y;
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			teapot_rotation += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}

void keypress(unsigned char key, int x, int y) {
	float cam_x,cam_z;
	float rads = teapot_rotation;
	
	cout << rads << endl;
	
	switch (key) {
		case CAM_MOVE_DOWN:
			teapot_x -= lx * 1.0;
			teapot_z -= lz * 1.0;
			break;

		case CAM_MOVE_UP:
			teapot_x += lx * 1;
			teapot_z += lz * 1;
			break;

		case CAM_ROT_CCW:
			teapot_rotation += 0.1f;
			lx = sin(teapot_rotation);
			lz = -cos(teapot_rotation);
			cout << "teapot is facing" << teapot_rotation << endl;
			break;

		case CAM_ROT_CW:
			teapot_rotation -= 0.1f;
			lx = sin(teapot_rotation);
			lz = -cos(teapot_rotation);
			cout << "teapot is facing" << teapot_rotation << endl;
			break;
		
		case CAM_ZOOM_OUT:
			cam_height++;
			cout << cam_height << endl;
			break;
	}
}

void isometric() {

	//set the clear color and clear the screen
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set up the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(VIEWING_ANGLE, 1.0, 1.0, 150.0);

	//render the world
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		gluLookAt(teapot_x, 1, teapot_z, teapot_x+lx, cam_height, teapot_z+lz, 0, 1.0,0.0);

		render_world(teapot_x, teapot_z, teapot_rotation * 57.2957795);
	glPopMatrix();

	glFlush();
}

void reshape(int width, int height) {
    glViewport(0,0,width,height);
}

void update(int value) {

	if (teapot_x < 0) teapot_x = 0;
	if (teapot_x > 9) teapot_x = 9;
	if (teapot_z < 0) teapot_z = 0;
	if (teapot_z > 9) teapot_z = 9;

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char* argv[] ){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	glutCreateWindow("Teapot World");
	glutDisplayFunc(isometric);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keypress);
	glutTimerFunc(25, update, 0);
	
	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mouseMove);

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glEnable(GL_DEPTH_TEST);
	

	/* turn on default lighting */
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambcolor);
    
    glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,lightpos);

	glutMainLoop();
	return 0;
}
