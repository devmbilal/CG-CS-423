#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Your drawing code for the sketchpad goes here
    glFlush();
}

void createMenu() {
    int menu = glutCreateMenu([](int){});
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Sketch Pad");

    createMenu();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
