#include <GL/glut.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

struct Point {
    double x, y;
};

std::vector<Point> fishBody;
std::vector<Point> fishTail;
Point fishEye;

void readCoordinates(const char* filename) {
    std::ifstream infile(filename);                                                                                                                            
    if (!infile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<Point>* currentVector = nullptr;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        double x, y;
        if (ss >> x >> y) {
            if (currentVector) {
                currentVector->push_back(Point{x, y});
            }
        } else {
            if (line.find("Fish Body") != std::string::npos) {
                currentVector = &fishBody;
            } else if (line.find("Fish Tail") != std::string::npos) {
                currentVector = &fishTail;
            } else if (line.find("Fish Eye") != std::string::npos) {
                std::getline(infile, line);
                std::stringstream ssEye(line);
                ssEye >> fishEye.x >> fishEye.y;
            }
        }
    }

    infile.close();
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Fish Body
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.5, 0.0); // Orange
    for (const auto& point : fishBody) {
        glVertex2d(point.x, point.y);
    }
    glEnd();

    // Fish Tail
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Red
    for (const auto& point : fishTail) {
        glVertex2d(point.x, point.y);
    }
    glEnd();

    // Fish Eye
    glColor3f(0.0, 0.0, 0.0); // Black
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2d(fishEye.x, fishEye.y);
    glEnd();

    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 1.0, 0.0);  // Blue background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Adjust for fish size
}

int main(int argc, char** argv) {
    const char* filename = "fish.txt";

    readCoordinates(filename);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Geometric Fish");
    init();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}
