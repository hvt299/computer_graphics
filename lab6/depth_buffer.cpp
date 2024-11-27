#include <GL/glut.h>

// Khoi tao toa do 2 hinh chu nhat
GLfloat rect1[4][3] = { // Hinh chu nhat 1
    {1.0, 1.0, 0.0},
    {2.0, 1.0, -2.0},
    {2.0, -1.0, -2.0},
    {1.0, -1.0, 0.0}
};

GLfloat rect2[4][3] = { // Hinh chu nhat 2
    {-1.0, 0.5, -1.0},
    {1.0, 0.5, -3.0},
    {1.0, -0.5, -3.0},
    {-1.0, -0.5, -1.0}
};

// Ham ve he truc Oxyz
void drawAxes() {
    glColor3f(1.0, 0.0, 0.0); // Truc Ox (do)
    glBegin(GL_LINES);
    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(4.0, 0.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0); // Truc Oy (xanh la)
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 4.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0); // Truc Oz (xanh duong)
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -50.0);
    glVertex3f(0.0, 0.0, 4.0);
    glEnd();
}

// Ham ve hinh chu nhat
void drawRectangles() {
	// Ve hinh chu nhat 1 (mau tim)
    glColor3f(0.5, 0.0, 0.5);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glVertex3fv(rect1[i]);
    }
    glEnd();
	
    // Ve hinh chu nhat 2 (mau cyan)
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glVertex3fv(rect2[i]);
    }
    glEnd();
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(3.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    drawAxes();        // Ve he truc Oxyz
    drawRectangles();  // Ve hai hinh chu nhat

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void initGL() {
    glEnable(GL_DEPTH_TEST); // Bat Depth Buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    int mode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;
    glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("Thuat toan Depth-buffer (Z-buffer)");
    
    initGL();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
