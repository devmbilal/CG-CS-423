#include <GL/glut.h>
#include <vector>
#include <iostream>

enum DrawMode { NONE, DRAW_POINT, LINE, POLYLINE, POLYGON, RECTANGLE };

struct Point {
    float x, y;
};

std::vector<Point> points;
DrawMode currentMode = NONE;
float lineWidth = 1.0f;
float pointSize = 1.0f;
float drawColor[3] = { 0.0f, 0.0f, 0.0f };
float bgColor[3] = { 1.0f, 1.0f, 1.0f };

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3fv(drawColor);
    glLineWidth(lineWidth);
    glPointSize(pointSize);

    // Debug: Print points being drawn
    std::cout << "Drawing points: ";
    for (std::vector<Point>::const_iterator it = points.begin(); it != points.end(); ++it) {
        std::cout << "(" << it->x << ", " << it->y << ") ";
    }
    std::cout << std::endl;

    glBegin(GL_POINTS);
    for (std::vector<Point>::const_iterator it = points.begin(); it != points.end(); ++it) {
        glVertex2f(it->x, it->y);
    }
    glEnd();

    if (currentMode == POLYLINE || currentMode == POLYGON || currentMode == RECTANGLE) {
        glBegin(GL_LINE_STRIP);
        for (std::vector<Point>::const_iterator it = points.begin(); it != points.end(); ++it) {
            glVertex2f(it->x, it->y);
        }
        if (currentMode == POLYGON && !points.empty()) {
            glVertex2f(points[0].x, points[0].y);
        }
        glEnd();
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Point p = { (float)x, (float)(glutGet(GLUT_WINDOW_HEIGHT) - y) };
        points.push_back(p);
        std::cout << "Added point: (" << p.x << ", " << p.y << ")" << std::endl;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'c':
        points.clear();
        std::cout << "Cleared all points" << std::endl;
        glutPostRedisplay();
        break;
    case 'u':
        if (!points.empty()) points.pop_back();
        std::cout << "Removed last point" << std::endl;
        glutPostRedisplay();
        break;
    }
}

void setDrawMode(int mode) {
    currentMode = (DrawMode)mode;
    points.clear();
    std::cout << "Set draw mode: " << currentMode << std::endl;
    glutPostRedisplay();
}

void setLineWidth(int widthChange) {
    lineWidth += widthChange;
    if (lineWidth < 1.0f) lineWidth = 1.0f;
    std::cout << "Set line width: " << lineWidth << std::endl;
    glutPostRedisplay();
}

void setPointSize(int sizeChange) {
    pointSize += sizeChange;
    if (pointSize < 1.0f) pointSize = 1.0f;
    std::cout << "Set point size: " << pointSize << std::endl;
    glutPostRedisplay();
}

void setColor(float r, float g, float b) {
    drawColor[0] = r;
    drawColor[1] = g;
    drawColor[2] = b;
    std::cout << "Set draw color: (" << r << ", " << g << ", " << b << ")" << std::endl;
    glutPostRedisplay();
}

void setBgColor(float r, float g, float b) {
    bgColor[0] = r;
    bgColor[1] = g;
    bgColor[2] = b;
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
    std::cout << "Set background color: (" << r << ", " << g << ", " << b << ")" << std::endl;
    glutPostRedisplay();
}

void createMenu() {
    int drawMenu = glutCreateMenu(setDrawMode);
    glutAddMenuEntry("Draw Point", DRAW_POINT);
    glutAddMenuEntry("Draw Line", LINE);
    glutAddMenuEntry("Draw Polyline", POLYLINE);
    glutAddMenuEntry("Draw Polygon", POLYGON);
    glutAddMenuEntry("Draw Rectangle", RECTANGLE);

    int lineWidthMenu = glutCreateMenu(setLineWidth);
    glutAddMenuEntry("Increase Width", 1);
    glutAddMenuEntry("Decrease Width", -1);

    int pointSizeMenu = glutCreateMenu(setPointSize);
    glutAddMenuEntry("Increase Size", 1);
    glutAddMenuEntry("Decrease Size", -1);

    int colorMenu = glutCreateMenu([](int color) {
        switch (color) {
        case 1: setColor(1.0f, 0.0f, 0.0f); break; // Red
        case 2: setColor(0.0f, 1.0f, 0.0f); break; // Green
        case 3: setColor(0.0f, 0.0f, 1.0f); break; // Blue
        case 4: setColor(0.0f, 0.0f, 0.0f); break; // Black
        }
    });
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Black", 4);

    int bgColorMenu = glutCreateMenu([](int color) {
        switch (color) {
        case 1: setBgColor(1.0f, 1.0f, 1.0f); break; // White
        case 2: setBgColor(0.0f, 0.0f, 0.0f); break; // Black
        case 3: setBgColor(0.5f, 0.5f, 0.5f); break; // Gray
        }
    });
    glutAddMenuEntry("White", 1);
    glutAddMenuEntry("Black", 2);
    glutAddMenuEntry("Gray", 3);

    glutCreateMenu(0);
    glutAddSubMenu("Draw Mode", drawMenu);
    glutAddSubMenu("Line Width", lineWidthMenu);
    glutAddSubMenu("Point Size", pointSizeMenu);
    glutAddSubMenu("Drawing Color", colorMenu);
    glutAddSubMenu("Background Color", bgColorMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Sketch Pad");

    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    createMenu();
    glutMainLoop();
    return 0;
}
