#include <windows.h>
#include <GL/glut.h>
#include <math.h>

// Define A, B, C, D
GLdouble A = 1.0, B = 0.0, C = 1.0, D = 0.0;

void myDisplay(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);           
  for (GLdouble x=0; x<4.0; x += 0.005) {
    GLdouble func = exp(-x)*cos(2*3.14159265*x);
    glVertex2d( A*x + B, C*func + D ); 
  }
  glEnd(); 
  glFlush();
}

void myInit(void) {
  glClearColor(1.0,1.0,1.0,0.0); 
  glColor3f(0.0f, 0.0f, 0.0f); 
  glPointSize(2.0); 
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity(); 
  gluOrtho2D(0.0, 4.0, -2.0, 2.0); 
}

int main(int argc, char** argv) {
  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
  glutInitWindowSize(100,200); 
  glutInitWindowPosition(100, 150);             
  glutCreateWindow("Dot Plot of a Function"); 
  glutDisplayFunc(myDisplay);                 
  myInit();
  glutMainLoop();
  return 0;
}
