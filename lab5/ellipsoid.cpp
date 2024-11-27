#include <GL/glut.h>
#include <cmath>

// Ham ve mat elipsoid
void drawEllipsoid(float radiusX, float radiusY, float radiusZ, int slices, int stacks) {
    float uStep = 2.0f * M_PI / slices; // Buoc cho u
    float vStep = M_PI / stacks;       // Buoc cho v

    for (int i = 0; i < stacks; ++i) {
        float v0 = i * vStep;
        float v1 = v0 + vStep;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float u = j * uStep;

            // Diem tren vong dau tien
            float x0 = radiusX * cos(u) * sin(v0);
            float y0 = radiusY * sin(u) * sin(v0);
            float z0 = radiusZ * cos(v0);

            // Diem tren vong thu hai
            float x1 = radiusX * cos(u) * sin(v1);
            float y1 = radiusY * sin(u) * sin(v1);
            float z1 = radiusZ * cos(v1);

            glVertex3f(x0, y0, z0);
            glVertex3f(x1, y1, z1);
        }
        glEnd();
    }
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(10, 5, 5, 0, 0, 0, 0, 0, 1);
    
    glTranslatef(0.0f, 0.0f, -1.0f);  // Di chuyen xa de de quan sat
    
    // Ve mat elipsoid
    glColor3f(1.0f, 1.0f, 0.0f); // Mau vang
    drawEllipsoid(3.0f, 3.0f, 0.5f, 30, 30);
    
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
    glutCreateWindow("Ve mat Elipsoid");
    
    initGL();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
