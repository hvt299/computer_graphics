#include <GL/glut.h>
#include <cmath>

// Cau hinh anh sang
void initLighting() {
    glEnable(GL_LIGHTING); // Bat anh sang
    glEnable(GL_LIGHT0);   // Su dung nguon sang 0
    GLfloat lightPos[] = {1.0f, 1.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
}

void initGL() {
    glEnable(GL_DEPTH_TEST); // Bat kiem tra do sau
    glEnable(GL_NORMALIZE);  // Binh thuong hoa vector phap tuyen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Ham ve mat cau
void drawSphere() {
    // Dinh nghia mau vat lieu (mau cam)
    GLfloat materialAmbient[] = {0.8f, 0.4f, 0.1f, 1.0f};  // Mau moi truong (ambient)
    GLfloat materialDiffuse[] = {0.8f, 0.4f, 0.1f, 1.0f};  // Mau khuech tan (diffuse)
    GLfloat materialSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Mau phan chieu (specular)
    GLfloat materialShininess[] = {32.0f};                 // Do bong (shininess)

    // Gan mau vat lieu cho anh sang
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

    // Ve mat cau
    glutSolidSphere(0.5, 50, 50); // Ban kinh 0.5, phan manh 50x50
}

// Ham to bong hang Lambert
void displayLambert() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_FLAT); // To bong phang (Flat shading)
    initLighting();        // Khoi tao anh sang

    glPushMatrix();
    glRotatef(30.0, 1.0, 1.0, 0.0); // Xoay mat cau de de quan sat
    drawSphere();
    glPopMatrix();

    glutSwapBuffers();
}

// Ham to bong noi suy Gouraud
void displayGouraud() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH); // To bong min (Smooth shading - Gouraud)
    initLighting();          // Khoi tao anh sang

    glPushMatrix();
    glRotatef(30.0, 1.0, 1.0, 0.0); // Xoay mat cau de de quan sat
    drawSphere();
    glPopMatrix();

    glutSwapBuffers();
}

// Ham to bong noi suy Phong
void displayPhong() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH); // To bong min (OpenGL khong ho tro truc tiep Phong shading)
    initLighting();          // Khoi tao anh sang

    glPushMatrix();
    glRotatef(30.0, 1.0, 1.0, 0.0); // Xoay mat cau de de quan sat
    drawSphere();
    glPopMatrix();

    glutSwapBuffers();
}

// Ham khong to bong
void displayNoShading() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);      // Tat anh sang
    glColor3f(0.8f, 0.4f, 0.1f); // Mau co dinh cho mat cau

    glPushMatrix();
    glRotatef(30.0, 1.0, 1.0, 0.0); // Xoay mat cau de de quan sat
    drawSphere();
    glPopMatrix();

    glutSwapBuffers();
}

int mode = 0;

void mydisplay() {
    switch (mode) {
        case 0: displayNoShading(); break;
        case 1: displayLambert(); break;
        case 2: displayGouraud(); break;
        case 3: displayPhong(); break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'n') mode = 0; // Khong to bong
    if (key == 'l') mode = 1; // Lambert
    if (key == 'g') mode = 2; // Gouraud
    if (key == 'p') mode = 3; // Phong
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    int mode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;
    glutInitDisplayMode(mode);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("To bong hang Lambert, noi suy Gouraud, Phong");
    
    initGL();
    glutDisplayFunc(mydisplay);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
