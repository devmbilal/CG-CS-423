#include <GL/glut.h>

void MY_Init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
    glColor3f(1.0, 0.0, 0.0);


}


void Draw() {
    glBegin(GL_LINE_LOOP);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.6, 0.6, 0.6);
    glRecti(70,70,150,150);
    glColor3f(0.2, 0.2, 0.2);
    glRecti(70,50,150,130);
    glEnd();
    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("simple");
    MY_Init();
    glutDisplayFunc(Draw);
    glutMainLoop();

  //  return 0;
}


