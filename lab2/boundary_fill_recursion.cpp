#include <GL/glut.h>

void initGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(0, 640, 0, 480, -1, 1);
}

void boundaryFill(int x, int y, float* fillColor, float* bc){
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2])
        && (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])){
        
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
        glFlush();

        boundaryFill(x+1, y, fillColor, bc);
        boundaryFill(x-2, y, fillColor, bc);
        boundaryFill(x, y+2, fillColor, bc);
        boundaryFill(x, y-2, fillColor, bc);
    }
}

void mydisplay() {
	glLineWidth(3);
    glPointSize(2);

    glClear(GL_COLOR_BUFFER_BIT);

    // Ve hinh tam giac
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();
    
    // Thuc hien to mau
    float bCol[] = {0.0, 0.0, 0.0};
    float color[] = {1.0, 0.0, 0.0};
	boundaryFill(300, 150, color, bCol);

	glViewport(0, 0, 640, 480);
    glFlush();
}

int main(int argc, char** argv){
    int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
	glutInitWindowPosition(800, 150);
    glutCreateWindow("TO MAU THEO DUONG BIEN BANG THUAT TOAN BOUNDARY FILL SU DUNG DE QUY");
    
    initGL();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
