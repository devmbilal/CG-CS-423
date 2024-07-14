#include <GL/glut.h>
#include <fstream>
#include <vector>

struct Point {
    float x, y;
};

std::vector<Point> points;

void readData() {
    std::ifstream file("coordinates.dat");
    Point p;
    while (file >> p.x >> p.y) {
        points.push_back(p);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for (auto &p : points) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    readData();
    glutInit(&argc, argv);
    glutCreateWindow("Reading coordinates from file");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}