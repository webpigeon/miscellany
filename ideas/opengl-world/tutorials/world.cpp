#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define CAM_MOVE_UP 'w'
#define CAM_MOVE_LEFT 'a'
#define CAM_MOVE_RIGHT 'd'
#define CAM_MOVE_DOWN 's'

using namespace std;

double theta = 45.0, phi=45.0;
double pos=4.0;

void printVertex() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(54,1.0,1.0,50.0);

	/* use this length so that camera is 1 unit away from origin */
	double dist = sqrt(1 / 3.0);

	gluLookAt(dist, dist, dist,  /* position of camera */
        	  0.0,  0.0,  0.0,   /* where camera is pointing at */
       		   0.0,  1.0,  0.0);  /* which direction is up */
	glMatrixMode(GL_MODELVIEW);

	float xeye = pos * cos(phi*M_PI/180.0) * cos(theta*M_PI/180.0);
	float yeye = pos * cos(phi*M_PI/180.0) * sin(theta*M_PI/180.0);
  	float zeye = pos * sin(phi*M_PI/180.0);
  
  	gluLookAt(xeye,yeye,zeye,
		0.0,0.0,0.0,   
		0.0,0.0,1.0);  

	glBegin(GL_LINES);

	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 0.0);

	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 1.0, 0.0);

	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 1.0);

	glEnd();

	glFlush();
}

void reshape (int width, int height) {
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]){

	/* Init Glut using command line args */
	glutInit(&argc, argv);

	//Set the window size, display type and position
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_RGB);

	//Create and display the glut window
	glutCreateWindow("Fracture RPG");


	//glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutDisplayFunc(printVertex);


	//enter glut main loop
	glutMainLoop();
}
