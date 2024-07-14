#include <GL/glut.h>

void drawSquare(int x, int y, int size) {
    glBegin(GL_QUADS);
    glVertex2f(x * size, y * size);
    glVertex2f(x * size, (y + 1) * size);
    glVertex2f((x + 1) * size, (y + 1) * size);
    glVertex2f((x + 1) * size, y * size);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int size = 40; // size of each square
    int rows = 10; // number of rows
    int cols = 5; // number of columns

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // alternate colors
            if ((i + j) % 2 == 0) {
                glColor3f(0.0, 0.0, 0.0); // black
            } else {
                glColor3f(1.0, 1.0, 1.0); // white
            }

            // draw square
            drawSquare(i, j, size);
        }
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Chessboard");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}