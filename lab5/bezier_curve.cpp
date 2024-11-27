#include <GL/glut.h>
#include <cmath>

// Ham ve duong cong bezier (vi du don gian voi 4 diem dieu khien)
void drawBezierCurve() {
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
        float x = pow(1 - t, 3) * (-1.0f) + 3 * pow(1 - t, 2) * t * 0.0f + 3 * (1 - t) * pow(t, 2) * 1.0f + pow(t, 3) * 1.0f;
        float y = pow(1 - t, 3) * 0.0f + 3 * pow(1 - t, 2) * t * 1.0f + 3 * (1 - t) * pow(t, 2) * 1.0f + pow(t, 3) * 0.0f;
        glVertex2f(x, y);
    }
    glEnd();
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(10, 5, 5, 0, 0, 0, 0, 0, 1);
    
    glTranslatef(0.0f, 0.0f, -1.0f);  // Di chuyen xa de de quan sat
    
    // Ve duong cong bezier
    glColor3f(1.0f, 0.0f, 1.0f); // Mau hong
    drawBezierCurve();
    
    glutSwapBuffers();
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

// Ham cau hinh cua so
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (double)w / (double)h, 1.0f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    int mode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;
    glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("Ve duong cong Bezier");
    
    initGL();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
