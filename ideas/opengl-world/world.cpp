#include <GL/glut.h>

void setMaterial ( GLfloat ambientR, GLfloat ambientG, GLfloat ambientB, 
		   GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB, 
		   GLfloat specularR, GLfloat specularG, GLfloat specularB,
		   GLfloat shininess ) {

    GLfloat ambient[] = { ambientR, ambientG, ambientB };
    GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
    GLfloat specular[] = { specularR, specularG, specularB };

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
}

void floorTile(int x, int z){
	setMaterial(1.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,1);
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_QUADS);
		glVertex3f(x, 0.0, z);
		glVertex3f(x+1, 0.0, z);
		glVertex3f(x+1, 0.0, z+1);
		glVertex3f(x, 0.0, z+1);
	glEnd();

}

void wallSegmentX(int x, int z){
	setMaterial(0.0,0.5,1.0,0.0,0.5,1.0,1.0,1.0,1.0,1);
	glColor4f(0.5,0.5,0.5, 0.5);
	glBegin(GL_QUADS);
		glVertex3f(x, 2.0, z);
		glVertex3f(x+1, 2.0, z);
		glVertex3f(x+1, 0.0, z);
		glVertex3f(x, 0.0, z);
	glEnd();

}

void wallSegmentZ(int x, int z){
	setMaterial(0.0,0.5,0.5,0.0,0.5,1.0,1.0,1.0,1.0,1);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
		glVertex3f(x, 2.0, z);
		glVertex3f(x, 2.0, z+1);
		glVertex3f(x, 0.0, z+1);
		glVertex3f(x, 0.0, z);
	glEnd();
}

void doorX(int x, int z){
	setMaterial(1.0,1.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.5);
	glColor3f(205/255.0,183/255.0,158/255.0);
	glBegin(GL_QUADS);
		glVertex3f(x+0.15, 0.0, z+0.01);
		glVertex3f(x+0.85, 0.0, z+0.01);
		glVertex3f(x+0.85, 1.8, z+0.01);
		glVertex3f(x+0.15, 1.8, z+0.01);
	glEnd();
}

void render_teapot(int x, int z, float rotation) {
	setMaterial(0.5,0.5,0.5,0.9,0.0,0.0,0.0,0.0,0.0,0.5);
	glPushMatrix();
		glTranslatef(x+0.5, 1, z+0.5);
		glRotatef(rotation, 0, 1, 0);
		glTranslatef(-(x+0.5), -1, -(z+0.5) );
		
		glTranslatef(x+.5, 1, z);
		glColor3f(1, 1, 1);
		glutWireTeapot(1);
	glPopMatrix();
}

void render_world(int tp_x, int tp_z, float rotation) {
	for (int x=0; x<10; x++){
		wallSegmentX(x,0);
		
		for(int y=0; y<10; y++){
			floorTile(x, y);
		}
		
		wallSegmentX(x,10);
	}
	
	for (int n=0; n<10; n++){
		wallSegmentZ(0, n);
		wallSegmentZ(10, n);
	}

	doorX(5,0);
}
