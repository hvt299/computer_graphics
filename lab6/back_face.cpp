#include <GL/glut.h>
#include <iostream>

// Tap dinh
float vertices[5][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 0.0, -1.0},
    {-1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0}
};

void drawAxes() {
    // Ve truc Ox (mau do)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-3.0, 0.0, 0.0);
    glVertex3f(3.0, 0.0, 0.0);
    glEnd();

    // Ve truc Oy (mau xanh la)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0);
    glEnd();

    // Ve truc Oz (mau xanh duong)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -3.0);
    glVertex3f(0.0, 0.0, 3.0);
    glEnd();
}

void drawObject() {
    glEnable(GL_CULL_FACE);  // Bat tính nang khu mat khuat
    glCullFace(GL_BACK);     // Khu cac mat sau
    glFrontFace(GL_CCW);     // Mat phia truoc la cac mat co dinh huong nguoc chieu kim dong ho

    // Ve cac mat cua khoi
    glBegin(GL_TRIANGLES);

    // Mat truoc (1, 5, 4) - Mau cyan
    glColor3f(0.0, 1.0, 1.0);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[3]);

    // Mat trai (3, 4, 5) - Mau vang
    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[4]);

    // Mat phai (1, 2, 5) - Mau tim
    glColor3f(0.5, 0.0, 0.5);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[4]);

    // Mat sau (2, 3, 5) - Mau xanh la
    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[4]);

    glEnd();

    // Mat duoi (1, 4, 3, 2) - Mau cam
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 0.0);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[1]);
    glEnd();

    glDisable(GL_CULL_FACE); // Tat tinh nang khu mat khuat
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0); // Diem nhin

    drawAxes();   // Ve he truc Oxyz
    drawObject(); // Ve doi tuong

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0); // Phep chieu phoi canh
    glMatrixMode(GL_MODELVIEW);
}

void initGL() {
	glDisable(GL_DEPTH_TEST); // Vo hieu hoa Depth Buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    int mode = GLUT_DOUBLE | GLUT_RGB;
    glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("Thuat toan khu mat sau (Back-face)");
    
    initGL();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
