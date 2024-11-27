#include <GL/glut.h>
#include <math.h>

void initGL() {
	glClearColor(1.1f, 1.0f, 1.0f, 1.0f); 
	glOrtho(-10, 10, -10, 10, -1, 1);
}

float vertices[] = {1.5, 1.5, 0, 1.5, 0, 0, 1.5, 0};

// Ham ve hinh chu nhat
void draw(void) {
	glBegin(GL_POLYGON);
		glVertex2f(vertices[0], vertices[1]);
		glVertex2f(vertices[2], vertices[3]);
		glVertex2f(vertices[4], vertices[5]);
		glVertex2f(vertices[6], vertices[7]);
	glEnd();
}

// Hàm ve duong thang y = ax + b
void drawLine(float a, float b) {
    float x1 = -9.0;
    float y1 = a * x1 + b;
    float x2 = 9.0;
    float y2 = a * x2 + b;

    // Ve doan thang noi 2 diem (x1, y1) va (x2, y2)
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Ve hinh chu nhat ban dau
	glColor3f(1, .5, .25);
	draw();
	
	// Ve duong thang y = ax + b (voi a = 1, b = 0)
    glColor3f(0, 0, 1);
    drawLine(1.0, 0.0);
    
    glFlush();
}

// Phep quay voi tam quay (x0, y0)
void rotate(float heso, float x0, float y0) {
    // Dich chuyen tat ca cac diem sao cho (x0, y0) trung voi goc toa do
    for (int i = 0; i < 8; i += 2) {
        vertices[i] -= x0;
        vertices[i + 1] -= y0;
    }

    // Thuc hien phep quay quanh goc (0, 0)
    for (int i = 0; i < 8; i += 2) {
        float x = vertices[i];
        float y = vertices[i + 1];
        vertices[i] = x * cos(heso * M_PI / 180) - y * sin(heso * M_PI / 180);
        vertices[i + 1] = x * sin(heso * M_PI / 180) + y * cos(heso * M_PI / 180);
    }

    // Dich chuyen lai cac diem ve vi tri ban dau
    for (int i = 0; i < 8; i += 2) {
        vertices[i] += x0;
        vertices[i + 1] += y0;
    }

    draw();
}

// Phep tinh tien theo truc Y
void changeY(float heso_tinh_tien) {
	vertices[0] += heso_tinh_tien;
	vertices[2] += heso_tinh_tien;
	vertices[4] += heso_tinh_tien;
	vertices[6] += heso_tinh_tien;
	draw();
}

// Phep tinh tien theo truc X
void changeX(float heso_tinh_tien) { 
	vertices[1] += heso_tinh_tien;
	vertices[3] += heso_tinh_tien;
	vertices[5] += heso_tinh_tien;
	vertices[7] += heso_tinh_tien;
	draw();
}

// Phep ti le voi tam ti le (x0, y0)
void scale(float heso_ti_le, float x0, float y0) {
    // Dich chuyen cac diem sao cho (x0, y0) trung voi goc toa do
    for (int i = 0; i < 8; i += 2) {
        vertices[i] -= x0;
        vertices[i + 1] -= y0;
    }

    // Thuc hien phep ti le quanh goc (0, 0)
    for (int i = 0; i < 8; i++) {
        vertices[i] *= heso_ti_le;
    }

    // Dich chuyen lai cac diem ve vi tri ban dau
    for (int i = 0; i < 8; i += 2) {
        vertices[i] += x0;
        vertices[i + 1] += y0;
    }

    draw();
}

// Phep doi xung qua duong thang y = ax + b
void reflect(float a, float b) {
	// Goc cua duong y = ax + b
    float theta = atan(a);

    // Dich chuyen toan bo he truc sao cho b = 0 (duong thang tro thanh y = ax)
    for (int i = 1; i < 8; i += 2) {
        vertices[i] -= b;  // Dich chuyen theo phuong Y
    }

    // Quay cac diem quanh goc toa do theo goc -theta de dua duong thang y = ax thanh truc hoanh
    for (int i = 0; i < 8; i += 2) {
        float x = vertices[i];
        float y = vertices[i + 1];
        vertices[i] = x * cos(-theta) - y * sin(-theta);
        vertices[i + 1] = x * sin(-theta) + y * cos(-theta);
    }

    // Thuc hien phep doi xung qua truc hoanh (doi dau cac gia tri y)
    for (int i = 1; i < 8; i += 2) {
        vertices[i] = -vertices[i];
    }

    // Quay nguoc lai cac diem theo goc theta de tro ve he truc ban dau
    for (int i = 0; i < 8; i += 2) {
        float x = vertices[i];
        float y = vertices[i + 1];
        vertices[i] = x * cos(theta) - y * sin(theta);
        vertices[i + 1] = x * sin(theta) + y * cos(theta);
    }

    // Dich chuyen nguoc lai theo phuong Y de dua ve he truc ban dau
    for (int i = 1; i < 8; i += 2) {
        vertices[i] += b;
    }

    draw();
}

void keyPressed(unsigned char key, int x, int y) {
	// Tam ti le hoac xoay
	float x0 = 0.5; float y0 = 0.5;
	// He so goc cua duong y = ax + b
	float a = 1.0;
	// Gia tri b trong duong y = ax + b
    float b = 0.0;
	
	switch (key) {
		// Nhan phim S hoac s de lay doi xung
        case 'S':
        case 's':
            reflect(a, b);
            break;
		
		// Nhan phim T hoac t tang kich thuoc
		case 'T':
		case 't':
			scale(1.2, x0, y0);
			break;
	
		// Nhan phim N hoac n giam kich thuoc
		case 'N':
		case 'n':
			scale(0.8, x0, y0);
			break;
	
		// Nhan phim L hoac l xoay trai
		case 'L':
		case 'l':
			rotate(-5, x0, y0);
			break;
	
		// Nhan phim R hoac r xoay phai
		case 'R':
		case 'r':
			rotate(5, x0, y0);
			break;
	}
}

void keypressSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {changeX(0.1);}    // Phim mui ten di len
	if (key == GLUT_KEY_DOWN) {changeX(-0.1);} // Phim mui ten di xuong
	if (key == GLUT_KEY_RIGHT) {changeY(0.1);} // Phim mui ten sang phai
	if (key == GLUT_KEY_LEFT) {changeY(-0.1);} // Phim mui ten sang trai
}

int main(int argc, char** argv) {
	int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
    glutInitWindowSize(640, 480);
	glutInitWindowPosition(800, 150);
	glutCreateWindow("CAC PHEP BIEN DOI 2D");
	
    initGL();
	glutDisplayFunc(mydisplay);
	glutIdleFunc(mydisplay);
	glutSpecialFunc(keypressSpecial);
	glutKeyboardFunc(keyPressed);  
	glutMainLoop();
}
