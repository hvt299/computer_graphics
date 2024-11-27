#include <GL/glut.h>
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 0.0f);	
	glBegin(GL_POLYGON);
		glVertex3f(-0.6, -0.75, 0.5);
		glVertex3f(0.6, -0.75, 0);
		glVertex3f(0, 0.75, 0);
	glEnd();
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Triangle");
	glutDisplayFunc(display);
	glutMainLoop();
}
