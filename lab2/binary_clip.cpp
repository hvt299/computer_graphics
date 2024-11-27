#include <GL/glut.h>
#include <cmath>

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

// Thuat toan chia nhi phan (binary clip)
void binaryClip(double x1, double y1, double x2, double y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Ca hai diem deu nam trong vung cat
            drawLine(x1, y1, x2, y2);
            break;
        } else if (code1 & code2) {
            // Ca hai diem deu ngoai cung mot vung cat
            break;
        } else if ((code1 != 0) && (code2 == 0)) {
        	// Hoan doi hai diem cho nhau
			double tmp;
			
			tmp = x1;
        	x1 = x2;
        	x2 = tmp;
        	
        	tmp = y1;
        	y1 = y2;
        	y2 = tmp;
        	
        	code1 = computeCode(x1, y1);
        	code2 = computeCode(x2, y2);
        } else if ((code1 == 0) && (code2 != 0)) {
        	double xp, yp, xq, yq, xm, ym;
        	
        	xp = x1; yp = y1;
			xq = x2; yq = y2;
			
			while ((fabs(xp-xq)+fabs(yp-yq)) > 2) {
				xm = (xp+xq)/2; ym = (yp+yq)/2;
				
				if (computeCode(xm, ym) == 0) {
					xp = xm;
					yp = ym;
				} else {
					xq = xm;
					yq = ym;
				}
			}
			
			drawLine(x1, y1, xp, yp);
			break;
        } else if (((code1 != 0) && (code2 != 0)) && ((code1 & code2) == 0)) {
			double xp, yp, xq, yq, xm, ym;
						
			xp = x1; yp = y1;
			xq = x2; yq = y2;
			xm = (xp+xq)/2; ym = (yp+yq)/2;
			
			while ((computeCode(xm, ym) != 0) && ((fabs(xp-xq)+fabs(yp-yq)) > 2)) {
				if (computeCode(xp, yp) & computeCode(xm, ym)) {
					xp = xm;
					yp = ym;
				} else {
					xq = xm;
					yq = ym;
				}
			}
			
			if (computeCode(xm, ym) == 0) {
				binaryClip(xp, yp, xm, ym);
				binaryClip(xm, ym, xq, yq);
			}
			break;
        }
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
    binaryClip(-160, -80, 160, 80);
    binaryClip(-70, 50, 70, 50);
    binaryClip(100, 100, 150, 150);
    
	glViewport(0, 0, 640, 480);
    glFlush();
}

int main(int argc, char** argv) {
    int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("XEN DOAN THANG TRONG HINH CHU NHAT BANG THUAT TOAN CHIA NHI PHAN");
    
    initGL();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
