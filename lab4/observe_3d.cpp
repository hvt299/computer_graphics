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

// Danh sach cac mat
int faces[6][4] = {
    {5, 6, 7, 8},
    {7, 8, 11, 12},
    {1, 2, 6, 5},
    {2, 3, 7, 6},
    {1, 4, 8, 5},
    {3, 4, 8, 7},
};

// Goc xoay alpha, theta va khoang cach quan sat
float alpha = 0.0, theta = 0.0;
float distance = 10.0;

// Phep chieu (0: song song, 1: phoi canh)
int projectionMode = 1;

// Ti le phong to/thu nho
float scaleFactor = 1.0;

// Che do hien thi vat the (0: khung ket noi, 1: mat da giac)
int renderMode = 0;

// Ham ve vat the dang khung ket noi
void drawWireframe() {
    glBegin(GL_LINES);
    for (int i = 0; i < 10; i++) {
        glVertex3fv(vertices[edges[i][0] - 1]);
        glVertex3fv(vertices[edges[i][1] - 1]);
    }
    glEnd();
}

// Ham ve vat the dung mat da giac
void drawPolygon() {
    // To mau cho hai mat dau tien
    for (int i = 0; i < 2; i++) {
        glColor3f(1.0, 1.0, 1.0); // Mau trang
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            glVertex3fv(vertices[faces[i][j] - 1]);
        }
        glEnd();
    }

    // Ve cac canh cua cac mat con lai dua tren tap canh
    glColor3f(1.0, 1.0, 1.0); // Mau trang
    glBegin(GL_LINES);
    for (int i = 0; i < 10; i++) { // Duyet qua danh sach cac canh
        glVertex3fv(vertices[edges[i][0] - 1]);
        glVertex3fv(vertices[edges[i][1] - 1]);
    }
    glEnd();
}

// Ham ve he truc Oxyz
void drawAxes() {
    glLineWidth(2.0);

    // Truc X (do)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-20.0, 0.0, 0.0);
    glVertex3f(20.0, 0.0, 0.0);
    glEnd();

    // Truc Y (xanh la)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -120.0, 0.0);
    glVertex3f(0.0, 120.0, 0.0);
    glEnd();

    // Truc Z (xanh duong)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -20.0);
    glVertex3f(0.0, 0.0, 20.0);
    glEnd();
}

// Ham thiet lap che do chieu
void setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (projectionMode == 1) {
        gluPerspective(45.0, 1.0, 1.0, 100.0); // Phoi canh
    } else {
        glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 100.0); // Song song
    }
    glMatrixMode(GL_MODELVIEW);
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Dat vi tri quan sat
    float eyeX = distance * cos(alpha) * cos(theta);
    float eyeY = distance * sin(theta);
    float eyeZ = distance * sin(alpha) * cos(theta);
    gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Ve he truc toa do
    drawAxes();

    // Ve vat the
    glPushMatrix();
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    glColor3f(1.0, 1.0, 1.0); // Mau trang cho vat the

    if (renderMode == 0) {
        drawWireframe();
    } else {
        drawPolygon();
    }

    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
	    case 'p': // Doi phep chieu (song song / phoi canh)
	        projectionMode = 1 - projectionMode;
	        setupProjection();
	        break;
	    case 'w': // Phong to
	        scaleFactor += 0.1;
	        break;
	    case 's': // Thu nho
	        scaleFactor -= 0.1;
	        if (scaleFactor < 0.1) scaleFactor = 0.1;
	        break;
	    case 'm': // Doi che do hien thi (khung ket noi / mat da giac)
	        renderMode = 1 - renderMode;
	        break;
	    case 27: // Thoat (phim Esc)
	        exit(0);
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
	    case GLUT_KEY_UP: // Tang goc theta
	        theta += 0.1;
	        break;
	    case GLUT_KEY_DOWN: // Giam goc theta
	        theta -= 0.1;
	        break;
	    case GLUT_KEY_LEFT: // Tang goc alpha
	        alpha -= 0.1;
	        break;
	    case GLUT_KEY_RIGHT: // Giam goc alpha
	        alpha += 0.1;
	        break;
	}
    glutPostRedisplay();
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    setupProjection();
}

int main(int argc, char** argv) {
    int mode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;
    glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("QUAN SAT VAT THE 3D");

    initGL();
    glutDisplayFunc(mydisplay);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
