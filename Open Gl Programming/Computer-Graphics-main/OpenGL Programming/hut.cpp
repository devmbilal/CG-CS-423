#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the base of the hut
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0); // Yellow color
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.0);
    glVertex2f(0.5, 0.0);
    glVertex2f(0.5, -0.5);
    glEnd();

    // Draw the roof of the hut
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Red color
    glVertex2f(-0.5, 0.0);
    glVertex2f(0.0, 0.5);
    glVertex2f(0.5, 0.0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL Hut");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}