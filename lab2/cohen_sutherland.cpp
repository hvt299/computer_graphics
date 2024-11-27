#include <GL/glut.h>

// Dinh nghia cac ma vung
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Gioi han cua hinh chu nhat cat (clip rectangle)
double x_min = -100, y_min = -80, x_max = 100, y_max = 80;

// Ham tinh toan ma vung cho 1 diem (x, y)
int computeCode(double x, double y) {
    int code = INSIDE;
    if (x < x_min) code |= LEFT;        // Trai vung cat
    else if (x > x_max) code |= RIGHT;  // Phai vung cat
    if (y < y_min) code |= BOTTOM;      // Duoi vung cat
    else if (y > y_max) code |= TOP;    // Tren vung cat
    return code;
}

void initGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-200, 200, -200, 200, -1, 1);
}

void drawLine(double x1, double y1, double x2, double y2) {
	glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

// Thuat toan Cohen-Sutherland
void cohenSutherlandClip(double x1, double y1, double x2, double y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Ca hai diem deu nam trong vung cat
            accept = true;
            break;
        } else if (code1 & code2) {
            // Ca hai diem deu ngoai cung mot vung cat
            break;
        } else {
            // Chon ma vung khong phai 0
            int code_out;
            double x, y;

            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Tim diem giao voi duong bien
            if (code_out & TOP) {
                // Diem nam tren vung cat
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) {
                // Diem nam duoi vung cat
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & RIGHT) {
                // Diem nam ben phai vung cat
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) {
                // Diem nam ben trai vung cat
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Thay the diem ngoai vung bang diem giao
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        // Doan thang sau khi duoc cat
        drawLine(x1, y1, x2, y2);
    }
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Ve hinh chu nhat 100 x 80
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x_min, y_min);
    glVertex2d(x_max, y_min);
    glVertex2d(x_max, y_max);
    glVertex2d(x_min, y_max);
    glEnd();

    // Ve doan thang y = 1x/2
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2d(-160, -80);
    glVertex2d(160, 80);
    glEnd();
    
    // Ve doan thang y = 50
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(-70, 50);
    glVertex2d(70, 50);
    glEnd();
    
    // Ve doan thang y = x
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2d(100, 100);
    glVertex2d(150, 150);
    glEnd();

    // Thuc hien cat doan thang
    cohenSutherlandClip(-160, -80, 160, 80);
    cohenSutherlandClip(-70, 50, 70, 50);
    cohenSutherlandClip(100, 100, 150, 150);
    
	glViewport(0, 0, 640, 480);
    glFlush();
}

int main(int argc, char** argv) {
    int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("XEN DOAN THANG TRONG HINH CHU NHAT BANG THUAT TOAN COHEN-SUTHERLAND");
    
    initGL();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
