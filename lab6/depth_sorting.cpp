#include <GL/glut.h>

// Cac dinh cua tam giac va hinh vuong
float vertices[7][3] = {
    {-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}, {0.0, -0.5, -0.5}, // Tam giac
    {-0.7, -0.2, 0.0}, {0.7, -0.2, 0.0}, {0.7, -0.7, 0.0}, {-0.7, -0.7, 0.0} // Hinh vuong
};

// Ham ve he truc Oxyz
void drawAxes() {
    glBegin(GL_LINES);
    // Truc Ox (do)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    // Truc Oy (xanh la)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);

    // Truc Oz (xanh duong)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

// Ve hinh tam giac
void drawTriangle() {
    glColor3f(1.0, 0.5, 0.0); // Mau cam
    glBegin(GL_TRIANGLES);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[2]);
    glEnd();
}

// Ve hinh vuong
void drawSquare() {
    glColor3f(1.0, 0.0, 1.0); // Mau hong
    glBegin(GL_QUADS);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[6]);
    glEnd();
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Dat camera
    gluLookAt(0.0, 0.0, 3.0,  // Vi tri camera
              0.0, 0.0, 0.0,  // Huong nhin
              0.0, 1.0, 0.0); // Huong len

    drawAxes(); // Ve he truc Oxyz
    
    // Sap xep thu cong va ve theo thu tu
    drawTriangle(); // Ve tam giac truoc (xa hon)
    drawSquare();   // Ve hinh vuong sau (gan hon)
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 10.0);
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
    glutCreateWindow("Thuat toan Depth-sorting (Painter)");

    initGL();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
