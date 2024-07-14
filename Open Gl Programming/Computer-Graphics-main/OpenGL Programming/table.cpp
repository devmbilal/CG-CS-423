#include <GL/glut.h>
#include <cmath>

void init() {
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f); // Light background
    glEnable(GL_DEPTH_TEST);
}

void drawTable() {
    glPushMatrix(); // Save transformation state

    // Tabletop
    glColor3f(0.5f, 0.35f, 0.05f); // Brown
    glTranslatef(0.0f, 0.0f, 0.75f); // Move up for table height
    glScalef(1.0f, 0.1f, 0.5f);  // Scale to table dimensions
    glutSolidCube(1.0);

    // Table legs (4)
    glColor3f(0.3f, 0.1f, 0.0f); // Darker brown
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glTranslatef((i % 2 == 0 ? -0.45f : 0.45f), -0.5f, (i < 2 ? -0.2f : 0.2f));
        glScalef(0.1f, 1.0f, 0.1f);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    glPopMatrix(); // Restore transformation state
}

void drawChair() {
    glPushMatrix();

    // Chair back
    glColor3f(0.8f, 0.6f, 0.4f); // Lighter brown
    glTranslatef(0.0f, 0.5f, 0.0f); 
    glScalef(0.8f, 1.0f, 0.1f);
    glutSolidCube(1.0);

    // Chair seat
    glTranslatef(0.0f, -0.55f, 0.4f); 
    glScalef(0.8f, 0.1f, 0.8f);
    glutSolidCube(1.0);

    // Chair legs (4)
    glColor3f(0.3f, 0.1f, 0.0f); 
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glTranslatef((i % 2 == 0 ? -0.35f : 0.35f), -0.5f, (i < 2 ? -0.35f : 0.35f));
        glScalef(0.1f, 1.0f, 0.1f);
        glutSolidCube(1.0);
        glPopMatrix();
    }
    
    glPopMatrix();
}
 
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Adjust camera position and perspective 
    gluLookAt(2.0, 1.5, 3.0,  // Eye position
              0.0, 0.0, 0.0,  // Look-at point
              0.0, 1.0, 0.0); // Up vector

    drawTable();
    glTranslatef(1.5f, 0.0f, 0.0f);  // Move the chair slightly
    drawChair();

    glutSwapBuffers(); 
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Table and Chair");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
