#include <GL/glut.h>
#include <cmath>

// Ham ve mat cong bezier (4 diem dieu khien)
void drawBezierSurface() {
    float controlPoints[4][4][3] = {
        {{-1.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, -1.0f, 0.0f}, {2.0f, -1.0f, 0.0f}},
        {{-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {2.0f, 0.0f, 0.0f}},
        {{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {2.0f, 1.0f, 0.0f}},
        {{-1.0f, 2.0f, 0.0f}, {0.0f, 2.0f, 0.0f}, {1.0f, 2.0f, 0.0f}, {2.0f, 2.0f, 0.0f}}
    };
    
    glBegin(GL_QUADS);
    for (float u = 0.0f; u <= 1.0f; u += 0.1f) {
        for (float v = 0.0f; v <= 1.0f; v += 0.1f) {
            float x = (1 - u) * (1 - v) * controlPoints[0][0][0] + u * (1 - v) * controlPoints[1][0][0] + (1 - u) * v * controlPoints[0][1][0] + u * v * controlPoints[1][1][0];
            float y = (1 - u) * (1 - v) * controlPoints[0][0][1] + u * (1 - v) * controlPoints[1][0][1] + (1 - u) * v * controlPoints[0][1][1] + u * v * controlPoints[1][1][1];
            float z = (1 - u) * (1 - v) * controlPoints[0][0][2] + u * (1 - v) * controlPoints[1][0][2] + (1 - u) * v * controlPoints[0][1][2] + u * v * controlPoints[1][1][2];
            glVertex3f(x, y, z);
        }
    }
    glEnd();
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(10, 5, 5, 0, 0, 0, 0, 0, 1);
    
    glTranslatef(0.0f, 0.0f, -1.0f);  // Di chuyen xa de de quan sat
    
    // Ve mat cong bezier
    glColor3f(0.0f, 1.0f, 1.0f); // Mau cyan
    drawBezierSurface();
    
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
    glutCreateWindow("Ve mat cong Bezier");
    
    initGL();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
