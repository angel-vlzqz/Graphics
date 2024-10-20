#include <GLUT/glut.h>
#include <cmath>

// Global variables for rotation
float rotationX = 0.0f;  // Rotation around the x-axis
float rotationY = 0.0f;  // Rotation around the y-axis

#define GRID_SIZE 50  // Define the grid resolution
#define SCALE 0.2f    // Scale the mesh size

// Function to compute z based on x and y (f(x, y) = sin(x) * cos(y))
float surfaceFunction(float x, float y) {
    return sin(x) * cos(y);
}

// Function to draw the mesh
void drawMesh() {
    glBegin(GL_QUADS);  // We will use quads for each grid cell

    for (int i = -GRID_SIZE; i < GRID_SIZE; i++) {
        for (int j = -GRID_SIZE; j < GRID_SIZE; j++) {
            // Calculate vertex positions based on the surface function
            float x1 = i * SCALE;
            float y1 = j * SCALE;
            float z1 = surfaceFunction(x1, y1);

            float x2 = (i + 1) * SCALE;
            float y2 = j * SCALE;
            float z2 = surfaceFunction(x2, y2);

            float x3 = (i + 1) * SCALE;
            float y3 = (j + 1) * SCALE;
            float z3 = surfaceFunction(x3, y3);

            float x4 = i * SCALE;
            float y4 = (j + 1) * SCALE;
            float z4 = surfaceFunction(x4, y4);

            // Draw the quad for this grid square
            glColor3f(0.0, 0.5 + z1, 1.0);  // Set a color gradient based on z-value
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);
        }
    }

    glEnd();
}

// Display function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear buffers

    glLoadIdentity();
    gluLookAt(0.0, -20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);  // Set camera position

    // Apply the rotations based on user input
    glRotatef(rotationX, 1.0, 0.0, 0.0);  // Rotate around x-axis
    glRotatef(rotationY, 0.0, 1.0, 0.0);  // Rotate around y-axis

    drawMesh();  // Call function to draw the mesh

    glutSwapBuffers();  // Swap buffers for smooth rendering
}

// Function to handle keyboard input for rotating the mesh
void handleKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':  // Rotate upwards
            rotationX -= 5.0f;
            break;
        case 's':  // Rotate downwards
            rotationX += 5.0f;
            break;
        case 'a':  // Rotate left
            rotationY -= 5.0f;
            break;
        case 'd':  // Rotate right
            rotationY += 5.0f;
            break;
        default:
            return;  // Ignore other keys
    }
    glutPostRedisplay();  // Request a redraw after the rotation
}

// Reshape function to adjust the viewport
void reshape(int width, int height) {
    glViewport(0, 0, width, height);  // Set the viewport to cover the new window size

    glMatrixMode(GL_PROJECTION);  // Switch to projection matrix
    glLoadIdentity();  // Reset projection matrix

    gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);  // Set perspective projection

    glMatrixMode(GL_MODELVIEW);  // Switch back to modelview matrix
}

// Initialization function
void init() {
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set background color to black
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple Mesh with WASD Rotation");

    init();  // Initialize OpenGL settings

    glutDisplayFunc(display);  // Set display function
    glutReshapeFunc(reshape);  // Set reshape function
    glutKeyboardFunc(handleKeys);  // Set keyboard input function for rotation
    glutMainLoop();  // Enter the GLUT event-processing loop

    return 0;
}