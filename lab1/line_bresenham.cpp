#include <GL/glut.h>
void initGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-320, 320, -240, 240, -1, 1);
}
void LineBres(int x1, int y1, int x2, int y2){
	
   	int x = x1;	int y = y1;
	int Dx = x2-x1; int Dy = y2-y1;
	
   	// Voi he so goc 0 < a < 1
	int p = 2*Dy-Dx;
	
	// Voi he so goc -1 < a < 0
	// int p = 2*Dy+Dx;
	
	// Voi he so goc a > 1
	// int p = 2*Dx-Dy;
	
	// Voi he so goc a < -1
	// int p = 2*Dx+Dy;
  	
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	while (x < x2){
		if (p < 0){
			// 0 < a < 1
			p += 2*Dy;
			
			// -1 < a < 0
			// p += 2*(Dy+Dx);
			// y--;	
		}else{
			// 0 < a < 1
            p += 2*(Dy-Dx);
			y++;
			
			// -1 < a < 0
			// p += 2*Dy;
		}
		x++;
        glVertex2i(x,y);
	}
	
	/* while (y < y2){
		if (p < 0){
			// a > 1
			p += 2*Dx;
			
			// a < -1
			// p += 2*(Dx+Dy);
			// x--;					
		}else{
			// a > 1
			p += 2*(Dx-Dy);
			x++;
			
			// a < -1
			// p += 2*Dx;
		}
		y++;
        glVertex2i(x,y);
	} */
	glEnd();
  	
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	// 0 < a < 1
	LineBres(0, 3, 200, 103);
	
	// -1 < a < 0
	// LineBres(0, 3, 200, -97);
	
	// a > 1
	// LineBres(0, 3, 100, 203);
	
	// a < -1
	// LineBres(100, -197, 0, 3);
	
	glViewport(0, 0, 640, 480);
	glFlush();
}

int main(int argc, char** argv){
	int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("VE DOAN THANG AB SU DUNG THUAT TOAN BRESENHAM");
	 
	initGL();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
