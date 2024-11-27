#include <GL/glut.h>
void initGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-10, 10, -10, 10, -1, 1);
}
void Hyperbol(){
  	glBegin(GL_LINE_STRIP);
	// Ve parabol voi ham so y = 1/x
	for (float x = -10.0f; x <= -0.1f; x += 0.01f) {
        float y = 1.0f / x;
        glVertex2f(x, y);
    }
    for (float x = 0.1f; x <= 10.0f; x += 0.01f) {
        float y = 1.0f / x;
        glVertex2f(x, y);
    }
	glEnd();
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	Hyperbol();
	glViewport(0, 0, 640, 480);
	glFlush();
}

int main(int argc, char** argv){
	int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("VE HYPERBOL y = 1/x");
	
	initGL();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
