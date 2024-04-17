
#include <GL/glut.h>
#include <cmath>

void drawStar() {
    float angle = 2.0f * 3.1416f / 5.0f; // Divide circle into 5 parts
    float halfAngle = angle / 2.0f;


    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 5; ++i) {
        glVertex2f(cos(i * angle), sin(i * angle));
        glVertex2f(0.5f * cos(i * angle + halfAngle), 0.5f * sin(i * angle + halfAngle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawStar();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL Star");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

