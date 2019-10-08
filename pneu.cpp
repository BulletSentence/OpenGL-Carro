#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLdouble pos_carro = 0;
GLdouble rot_rodas = 0;
int cam_view = 1;

void render_floor() {
	glColor3f(0.5, 0.8, 0.5);
	glBegin(GL_LINES);
	for (GLfloat i = -100; i <= 100; i += 10) {
		glVertex3f(i, -5, 100);
		glVertex3f(i, -5, -100);
		glVertex3f(100, -5, i);
		glVertex3f(-100, -5, i);
	}
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
 
	render_floor();

	glColor3f(0.0f, 0.0f, 0.0f);
	
	glPushMatrix();
	//Movimento do carro
	glTranslatef(pos_carro, 0, 0);
	
	//Cubo carro
	glPushMatrix();
	glTranslatef(0,2.5,0);
	glScalef(50, 5, 20);
	glutWireCube(1);
	glPopMatrix();
	
	glPushMatrix();
	glScalef(20, 10, 20);
	glTranslatef(0,0.5,0);
	glutWireCube(1);
	glPopMatrix();
	
	// Roda traseira direita
	glPushMatrix();
	glTranslatef(20, 0, -11);
	glutWireTorus(1.0, 3, 15, 30);
	glPopMatrix();

	// Roda traseira esquerda
	glPushMatrix();
	glTranslatef(20, 0, 11);
	glutWireTorus(1.0, 3, 15, 30);
	glPopMatrix();
	
	// Roda dianteira esquerda
	glPushMatrix();
	glTranslatef(-20, 0, 11);
	glRotatef(rot_rodas,0,1,0);
	glutWireTorus(1.0, 3, 15, 30);
	glPopMatrix();	
	
	// Roda dianteira direita
	glPushMatrix();
	glTranslatef(-20, 0, -11);
	glRotatef(rot_rodas,0,1,0);
	glutWireTorus(1.0, 3, 15, 30);
	glPopMatrix();
	
	// Roda traseira esquerda
	glPushMatrix();
	glTranslatef(20, 0, 11);
	glutWireTorus(1.0, 3, 15, 30);
	glPopMatrix();

	glPopMatrix();
	
	glutSwapBuffers();
}

void change_cam_view(){
  switch (cam_view) {
	case 0:
		gluLookAt(100, 0, 0, 0, 0, 0, 0, 1, 0);
		break;
	case 1:
		gluLookAt(100, 250, 0, 0, 0, 0, 0, 1, 0);
		break;
	case 2:
		gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);
		break;
	}
}

void configView() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glViewport(0, 0, 800, 600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, 800 / 600.0, 0.5, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  change_cam_view();

}

void resize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
}

void specialkeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		pos_carro += 2;
		break;
	case GLUT_KEY_DOWN:
		pos_carro -= 2;
		break;
	case GLUT_KEY_LEFT:
		rot_rodas -= 5;
		rot_rodas = (rot_rodas < -30) ? -30 : rot_rodas;
		break;
	case GLUT_KEY_RIGHT:
		rot_rodas += 5;
		rot_rodas = (rot_rodas > 30) ? 30 : rot_rodas;
		break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 27:
		exit(0);
		break;
	case 32:
		cam_view = (++cam_view % 3);
		pos_carro = 0;
		rot_rodas = 0;
		configView();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeys);
	configView();
	glutMainLoop();
	return 0;
}