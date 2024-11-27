#include <GL/glut.h>
#include <cmath>

// Ham ve mat torus
void drawTorus(float innerRadius, float outerRadius, int slices, int stacks) {
    glutWireTorus(innerRadius, outerRadius, slices, stacks);
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(10, 5, 5, 0, 0, 0, 0, 0, 1);
    
    glTranslatef(0.0f, 0.0f, -1.0f);  // Di chuyen xa de de quan sat
    
    // Ve mat torus
    glColor3f(1.0f, 0.5f, 0.0f); // Mau cam
    drawTorus(0.5f, 2.0f, 20, 20);
    
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
    glutCreateWindow("Ve mat Torus");
    
    initGL();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
