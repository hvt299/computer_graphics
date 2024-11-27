#include <GL/glut.h>
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f (1.0, 0.0, 0.0);
		glVertex3f (0.5, 0.5, 0.0);
		glColor3f (0.0, 1.0, 0.0);
		glVertex3f (-0.5, 0.5, 0.0);
		glColor3f (0.0, 0.0, 1.0);
		glVertex3f (-0.5, -0.5, 0.0);
		glColor3f (1.0, 1.0, 1.0);
		glVertex3f (0.5, -0.5, 0.0);
	glEnd();
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rectangle Colorful");
	glutDisplayFunc(display);
	glutMainLoop();
}
