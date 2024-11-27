#include <GL/glut.h>
#include <cmath>

// Ham ve mat hyperboloid
void drawHyperboloid(float baseRadius, float topRadius, float height, int slices, int stacks) {
    float stackHeight = height / stacks;
    float angleStep = 2 * M_PI / slices;

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < stacks; ++i) {
        float z0 = -0.5f * height + i * stackHeight;
        float z1 = z0 + stackHeight;

        float r0 = baseRadius + (topRadius - baseRadius) * (float)i / stacks;
        float r1 = baseRadius + (topRadius - baseRadius) * (float)(i + 1) / stacks;

        for (int j = 0; j <= slices; ++j) {
            float angle = j * angleStep;
            float x0 = r0 * cos(angle);
            float y0 = r0 * sin(angle);
            float x1 = r1 * cos(angle);
            float y1 = r1 * sin(angle);

            glVertex3f(x0, y0, z0);
            glVertex3f(x1, y1, z1);
        }
    }
    glEnd();
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(10, 5, 5, 0, 0, 0, 0, 0, 1);
    
    glTranslatef(0.0f, 0.0f, -1.0f);  // Di chuyen xa de de quan sat
    
    // Ve mat hyperboloid
    glColor3f(0.5f, 0.0f, 0.5f); // Mau tim
    drawHyperboloid(2.0f, 1.0f, 5.0f, 20, 20);
    
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
    glutCreateWindow("Ve mat Hyperboloid");
    
    initGL();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
