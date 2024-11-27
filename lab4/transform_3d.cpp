#include <GL/glut.h>
#include <cmath>

// Danh sach cac dinh
float vertices[12][3] = {
    {1, 1, -3}, {-1, 1, -3}, {-1, -1, -3}, {1, -1, -3},
    {1, 1, 0}, {-1, 1, 0}, {-1, -1, 0}, {1, -1, 0},
    {1, -1, 2}, {-1, -1, 2}, {1, -1, 3}, {-1, -1, 3}
};

// Danh sach cac canh
int edges[10][2] = {
    {1, 5}, {2, 6}, {3, 12}, {4, 11}, {5, 6},
    {6, 7}, {7, 8}, {8, 5}, {9, 10}, {11, 12}
};

// Ham ve vat the
void drawObject() {
    glBegin(GL_LINES);
    for (int i = 0; i < 10; i++) {
        glVertex3fv(vertices[edges[i][0] - 1]);
        glVertex3fv(vertices[edges[i][1] - 1]);
    }
    glEnd();
}

// Ve he truc Oxyz
void drawAxes() {
    glLineWidth(2.0); // Do day cua truc

    // Truc X (Mau do)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-90.0, 0.0, 0.0);
    glVertex3f(20.0, 0.0, 0.0);
    glEnd();

    // Truc Y (Mau xanh la)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -20.0, 0.0);
    glVertex3f(0.0, 20.0, 0.0);
    glEnd();

    // Truc Z (Mau xanh duong)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -20.0);
    glVertex3f(0.0, 0.0, 20.0);
    glEnd();
}

// Phep tinh tien
void translate(float tx, float ty, float tz) {
    for (int i = 0; i < 12; i++) {
        vertices[i][0] += tx;
        vertices[i][1] += ty;
        vertices[i][2] += tz;
    }
}

// Phep doi xung qua mat phang
void reflect(int plane) {
    for (int i = 0; i < 12; i++) {
        if (plane == 1) vertices[i][2] = -vertices[i][2]; // doi xung qua mat xoy
        else if (plane == 2) vertices[i][0] = -vertices[i][0]; // doi xung qua mat yoz
        else if (plane == 3) vertices[i][1] = -vertices[i][1]; // doi xung qua mat xoz
    }
}

// Phép ti le
void scale(float sx, float sy, float sz, float x0, float y0, float z0) {
    for (int i = 0; i < 12; i++) {
        vertices[i][0] = sx * (vertices[i][0] - x0) + x0;
        vertices[i][1] = sy * (vertices[i][1] - y0) + y0;
        vertices[i][2] = sz * (vertices[i][2] - z0) + z0;
    }
}

// Phep quay quanh truc toa do
void rotate(float angle, char axis) {
    float rad = angle * M_PI / 180.0; // Chuyen doi sang radian
    float cosA = cos(rad);
    float sinA = sin(rad);
    for (int i = 0; i < 12; i++) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        float z = vertices[i][2];
        if (axis == 'x') { // Quay quanh truc X
            vertices[i][1] = y * cosA - z * sinA;
            vertices[i][2] = y * sinA + z * cosA;
        } else if (axis == 'y') { // Quay quanh truc Y
            vertices[i][0] = x * cosA + z * sinA;
            vertices[i][2] = -x * sinA + z * cosA;
        } else if (axis == 'z') { // Quay quanh truc Z
            vertices[i][0] = x * cosA - y * sinA;
            vertices[i][1] = x * sinA + y * cosA;
        }
    }
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(20, 10, 10, 0, 0, 0, 0, 0, 1);

    // Ve he truc Oxyz
    drawAxes();

    // Dat mau cho vat the
    glColor3f(1.0, 1.0, 1.0); // Vat the mau trang
    // Ve vat the sau khi ap dung cac phep bien doi
    drawObject();

    glutSwapBuffers();
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
   	int mode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;
    glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("CAC PHEP BIEN DOI 3D");

    initGL();
    glutDisplayFunc(mydisplay);

    // Vi du ap dung cac phep bien doi
    translate(1, 2, 3);
    reflect(1); // Doi xung qua mat xoy
    scale(1.5, 1.5, 1.5, 0, 0, 0);
    rotate(-45, 'z'); // Quay -45 do quanh truc Z

    glutMainLoop();
    return 0;
}
