// #include <iostream>
// #include <fstream>
// #include <GL/glut.h> // Assuming you're using OpenGL

// using namespace std;

// void drawFishFile(const char *fileName) {
//     ifstream inStream(fileName); // open the file
//     if (!inStream.is_open()) {
//         cout << "Failed to open file: " << fileName << endl;
//         return;
//     }
    
//     GLint numPoints;
//     GLfloat x, y; // Update data types to GLfloat
//     // Read the number of points for the fish shape
//     if (!(inStream >> numPoints)) {
//         cout << "Failed to read number of points from file." << endl;
//         inStream.close();
//         return;
//     }
//     cout << "Number of points: " << numPoints << endl;
//     for (int i = 0; i < numPoints; i++) {
//     // Read the next x, y pair
//     if (!(inStream >> x >>y)) {
//         cout << "Failed to read point " << i+1 << " from file." << endl;
//         inStream.close();
//         return;
//     }

//     cout << "Point " << i+1 << ": (" << x << ", " << y << ")" << endl;
// }

//     inStream.close();
// }

// int main() {
//     drawFishFile("fish_coordinates.txt"); // Replace "fish.txt" with the path to your file
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <GL/glut.h>

using namespace std;

void drawFishFile(const char *fileName) {
    ifstream inStream(fileName);
    if (!inStream.is_open()) {
        cout << "Failed to open file: " << fileName << endl;
        return;
    }

    GLint numPoints;
    GLfloat x, y;
    if (!(inStream >> numPoints)) {
        cout << "Failed to read number of points from file." << endl;
        inStream.close();
        return;
    }

    // Array to store coordinates
    GLfloat *points = new GLfloat[numPoints * 2]; // 2 coordinates per point

    for (int i = 0; i < numPoints; i++) {
        if (!(inStream >> x >> y)) {
            cout << "Failed to read point " << i+1 << " from file." << endl;
            inStream.close();
            delete[] points; // Clean up dynamically allocated memory
            return;
        }
        points[i * 2] = x; // Store x coordinate
        points[i * 2 + 1] = y; // Store y coordinate
    }

    inStream.close();

    // OpenGL Drawing
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glColor3f(1.0, 0.0, 0.0); // Set color to red

    // Draw polyline
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < numPoints; i++) {
        glVertex2f(points[i * 2], points[i * 2 + 1]); // Draw each point
    }
    glEnd();

    // Display the result
    glutSwapBuffers();

    delete[] points; // Clean up dynamically allocated memory
}

void display() {
    drawFishFile("crow.txt");
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Fish Drawing");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10); // Set the coordinate system

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
