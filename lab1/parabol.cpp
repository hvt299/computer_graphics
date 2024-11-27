#include <GL/glut.h>
void initGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-10, 10, -10, 10, -1, 1);
}
void Parabol(){
  	glBegin(GL_LINE_STRIP);
	for (float x = -10.0f; x <= 10.0f; x += 0.01f) {
        float y = x * x; // Ve parabol voi ham so y = x^2
        glVertex2f(x, y);
    }
	glEnd();
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	Parabol();
	glViewport(0, 0, 640, 480);
	glFlush();
}

int main(int argc, char** argv){
	int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("VE PARABOL y = x^2");
	
	initGL();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
