#include <GL/glut.h>
#include <cmath>
void initGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-10, 10, -10, 10, -1, 1);
}
void Cosx(){
  	glBegin(GL_LINE_STRIP);
    for (float x = -10.0f; x <= 10.0f; x += 0.01f) {
        float y = cos(x); // Ve duong cong voi ham so y = cos(x)
        glVertex2f(x, y);
    }
	glEnd();
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	Cosx();
	glViewport(0, 0, 640, 480);
	glFlush();
}

int main(int argc, char** argv){
	int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("VE DUONG CONG y = cos(x)");
	
	initGL();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
