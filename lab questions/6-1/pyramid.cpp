#include <GLUT/glut.h>
#include <iostream>

int viewIndex = 0;

// Function to draw a pyramid
void drawPyramid() {
    glBegin(GL_TRIANGLES);

    // Front face
    glColor3f(1.0, 0.0, 0.0);  // Red
    glVertex3f(0.0, 1.0, 0.0);  // Top
    glVertex3f(-1.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, 1.0);

    // Right face
    glColor3f(0.0, 1.0, 0.0);  // Green
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, -1.0);

    // Back face
    glColor3f(0.0, 0.0, 1.0);  // Blue
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0, -1.0);

    // Left face
    glColor3f(1.0, 1.0, 0.0);  // Yellow
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0, 1.0);

    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);  // Gray
    glVertex3f(-1.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glEnd();
}

// Function to switch between camera views
void switchView() {
    switch (viewIndex) {
        case 0:
            gluLookAt(5.0, 3.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  // Camera further back
            break;
        case 1:
            gluLookAt(-5.0, 3.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  // Adjusted camera
            break;
        case 2:
            gluLookAt(0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);  // Top-down view
            break;
    }
}

// Keyboard input for switching views
void handleKeys(unsigned char key, int x, int y) {
    if (key == 'v') {
        viewIndex = (viewIndex + 1) % 3;
        glutPostRedisplay();
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear buffers
    glLoadIdentity();  // Reset modelview matrix

    switchView();  // Apply camera view

    // Draw pyramids
    glPushMatrix();
    glTranslatef(-2.5, 0.0, 0.0);  // Translate first pyramid
    drawPyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);  // Second pyramid at origin
    drawPyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, 0.0, 0.0);  // Translate third pyramid
    drawPyramid();
    glPopMatrix();

    glutSwapBuffers();  // Swap buffers
}

// Reshape function
void reshape(int width, int height) {
    glViewport(0, 0, width, height);  // Set viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Initialization
void init() {
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set background color to black
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Double buffering and depth buffer
    glutInitWindowSize(800, 600);  // Set the window size
    glutCreateWindow("OpenGL Pyramids with Switchable Views");  // Create the window with a title

    // Initialize OpenGL settings
    init();

    // Register callback functions
    glutDisplayFunc(display);  // Set display function for rendering
    glutReshapeFunc(reshape);  // Set reshape function when window is resized
    glutKeyboardFunc(handleKeys);  // Set keyboard function for user input

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}