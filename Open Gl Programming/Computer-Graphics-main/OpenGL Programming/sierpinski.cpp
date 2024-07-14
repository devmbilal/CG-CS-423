#include <GL/glut.h>
#include <stdlib.h>

void drawDot(int x, int y) { 
  glBegin(GL_POINTS);  // Start drawing points
  glVertex2i(x, y); // Specify the dot's coordinates
  glEnd();              // End drawing points
}

class GLintPoint {
public:
  GLint x, y; 
};

int random(int m) {
  return rand() % m; 
}

void Sierpinski(void) {
  GLintPoint T[3] = { {10,10}, {300, 30}, {200, 300} }; // Triangle vertices
  int index = random(3);                                // Random initial point
  GLintPoint point = T[index];
  drawDot( point.x, point.y);
  for (int i=0; i<1000; i++) {
    index = random(3);
    point.x = ( point.x + T[index].x ) / 2; // Midpoint calculation
    point.y = ( point.y + T[index].y ) / 2;
    drawDot( point.x, point.y);
  }
  glFlush(); 
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  Sierpinski();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Sierpinski Gasket");
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, 500.0, 0.0, 500.0);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}