#include <GL/glut.h>

struct StackNode {
    int x, y;
    StackNode* next;
};

StackNode* createNode(int x, int y) {
    StackNode* newNode = new StackNode();
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    return newNode;
}

void push(StackNode*& top, int x, int y) {
    StackNode* newNode = createNode(x, y);
    newNode->next = top;
    top = newNode;
}

bool pop(StackNode*& top, int &x, int &y) {
    if (top == NULL) return false;
    x = top->x;
    y = top->y;
    StackNode* temp = top;
    top = top->next;
    delete temp;
    return true;
}

bool isEmpty(StackNode* top) {
    return top == NULL;
}

void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(0, 640, 0, 480, -1, 1);
}

void boundaryFill(int x, int y, float* fillColor, float* bc) {
    StackNode* stack = NULL;
    push(stack, x, y);

    while (!isEmpty(stack)) {
        pop(stack, x, y);
        float color[3];
        glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
        if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) &&
            (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
            
			glColor3f(fillColor[0], fillColor[1], fillColor[2]);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            glFlush();

            push(stack, x+1, y);
            push(stack, x-2, y);
            push(stack, x, y+2);
            push(stack, x, y-2);
        }
    }
}

void mydisplay() {
    glLineWidth(3);
    glPointSize(2);

    glClear(GL_COLOR_BUFFER_BIT);
    
	// Ve hinh tam giac
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();
    
    // Thuc hien to mau
    float bCol[] = {0.0, 0.0, 0.0};
    float color[] = {1.0, 1.0, 0.0};
	boundaryFill(300, 150, color, bCol);

	glViewport(0, 0, 640, 480);
    glFlush();
}

int main(int argc, char** argv) {
    int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
	glutInitWindowPosition(800, 150);
    glutCreateWindow("TO MAU THEO DUONG BIEN BANG THUAT TOAN BOUNDARY FILL SU DUNG HANG DOI QUEUE");
    
    initGL();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
