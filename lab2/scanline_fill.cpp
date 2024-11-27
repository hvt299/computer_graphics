#include <GL/glut.h>
#include <algorithm>

// Khai bao cau truc diem
struct Point {
    float x, y;
};

// Khai bao da giac voi 5 diem co dinh
const int MAX_POINTS = 5;
Point polygon[MAX_POINTS] = {
	{100, 150},
	{200, 250},
	{300, 200},
	{250, 100},
	{150, 50}
};

void initGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(0, 500, 0, 500, -1, 1);
}

// Hàm ve 1 pixel
void setPixel(int x, int y) {
	glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Ham tim cac giao diem cua duong quet voi canh da giac
int findIntersections(int y, float intersections[]) {
    int count = 0;
    for (int i = 0; i < MAX_POINTS; i++) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % MAX_POINTS];

		// Bo qua canh ngang
        if (p1.y == p2.y) continue;
        // Khong co giao diem voi scanline
        if (y < std::min(p1.y, p2.y) || y > std::max(p1.y, p2.y)) continue;

        // Tinh toan toa do x cua diem giao
        float x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
        intersections[count++] = x;
    }
    // Tra ve so luong giao diem tim duoc
    return count;
}

// Ham thuc hien thuat toan to mau theo dong quet
void scanlineFill() {
	// Gioi han y quet
    int ymin = 50, ymax = 250;
    
    // Mang tam thoi chua cac giao diem
    float intersections[MAX_POINTS];

    for (int y = ymin; y <= ymax; y++) {
        // Tim cac giao diem cua duong quet voi da giac
        int count = findIntersections(y, intersections);

        // Sap xep cac giao diem theo thu tu tang dan
        std::sort(intersections, intersections + count);

        // To mau giua cac cap giao diem
        for (int i = 0; i < count; i += 2) {
            if (i + 1 < count) {
                for (int x = intersections[i]; x <= intersections[i + 1]; x++) {
                    setPixel(x, y);
                }
            }
        }
    }
}

void mydisplay() {
	glLineWidth(3);
    glPointSize(2);
	
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Ve da giac
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < MAX_POINTS; i++) {
        glVertex2f(polygon[i].x, polygon[i].y);
    }
    glEnd();

    // Thuc hien to mau
    scanlineFill();
    glViewport(0, 0, 640, 480);
    glFlush();
}

int main(int argc, char** argv) {
	int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
	glutInitWindowPosition(800, 150);
    glutCreateWindow("TO MAU THEO DONG QUET BANG THUAT TOAN SCANLINE FILL");
    
	initGL();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
