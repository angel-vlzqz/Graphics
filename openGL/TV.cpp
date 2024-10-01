#include <GLUT/glut.h>

// Function to initialize OpenGL settings
void initOpenGL() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for proper occlusion
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0); // Enable light #0
    glEnable(GL_COLOR_MATERIAL); // Enable color tracking

    // Set light properties
    GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, 5.0f, 5.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f); // Set the background color to light gray

    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0); // Setup the perspective projection

    glMatrixMode(GL_MODELVIEW); // Switch back to the modelview matrix
    glLoadIdentity();
}

// Function to draw a shelf with compartments
void drawTvStand() {
    // Draw the main shelf body
    glColor3f(0.2f, 0.13f, 0); // Brown color
    glPushMatrix();
    glScalef(4.0f, 1.0f, 1.5f); // Scale to resemble a TV stand
    glutSolidCube(1.0); // Draw the main shelf
    glPopMatrix();

    //Black color to draw cubbies and drawer divider
    glColor3f(0.0f, 0.0f, 0.0f); // Black color

    // Draw the right cubby
    glPushMatrix();
    glTranslatef(-1.3f, 0.23f, 0.51f); 
    glScalef(1.25f, 0.4f, 0.5f); // Scale to the desired size
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw the middle cubby
    glPushMatrix();
    glTranslatef(0.0f, 0.23f, 0.51f); 
    glScalef(1.25f, 0.4f, 0.5f); // Scale to the desired size
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw the right cubby
    glPushMatrix();
    glTranslatef(1.3f, 0.23f, 0.51f); 
    glScalef(1.25f, 0.4f, 0.5f); // Scale to the desired size
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.05f, 0.0325f, 0.0f);

    //Draw the left drawer divider
    glPushMatrix();
    glTranslatef(-.65f,-.245f, 0.51f);
    glScalef(.05f,.45f, 0.5f);
    glutSolidCube(1);
    glPopMatrix();
    
    //Draw the right drawer divider
    glPushMatrix();
    glTranslatef(.65f,-.245f, 0.51f);
    glScalef(.05f,.45f, 0.5f);
    glutSolidCube(1);
    glPopMatrix();


    //Grey/silver color to draw the drawers
    glColor3f(0.32f,0.32f,0.32f);

    //Left Drawer panel
    glPushMatrix();
    glTranslatef(-1.3f, -0.25f, 0.505f); 
    glScalef(1.0f, 0.3f, 0.5f); 
    glutSolidCube(1.0);
    glPopMatrix();

    //middle Drawer panel
    glPushMatrix();
    glTranslatef(0.0f, -0.25f, 0.505f); 
    glScalef(1.0f, 0.3f, 0.5f); 
    glutSolidCube(1.0);
    glPopMatrix();

    //right Drawer panel
    glPushMatrix();
    glTranslatef(1.3f, -0.25f, 0.505f); 
    glScalef(1.0f, 0.3f, 0.5f); 
    glutSolidCube(1.0);
    glPopMatrix();


    //dark Grey color to draw the drawer handle
    glColor3f(0.15f,0.15f,0.15f);

    //left drawer handle
    glPushMatrix();
    glTranslatef(-1.3f, -0.03f, 0.51f); 
    glScalef(0.4f, 0.05f, 0.5f); 
    glutSolidCube(1.0);
    glPopMatrix();

     //middle drawer handle
    glPushMatrix();
    glTranslatef(0.0f, -0.03f, 0.51f); 
    glScalef(0.4f, 0.05f, 0.5f); 
    glutSolidCube(1.0);
    glPopMatrix();

     //right drawer handle
    glPushMatrix();
    glTranslatef(1.3f, -0.03f, 0.51f); 
    glScalef(0.4f, 0.05f, 0.5f); 
    glutSolidCube(1.0);
    glPopMatrix();

}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and the depth buffer
    glLoadIdentity(); // Reset the modelview matrix

    // Setup the camera view
    gluLookAt(0.0f, 2.0f, 5.0f,  // Camera position
              0.0f, 0.0f, 0.0f,  // Look at point (origin)
              0.0f, 1.0f, 0.0f); // Up vector

    // Draw the TV stand and compartments
    drawTvStand();

    // Draw the TV screen
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for TV screen
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f); // Move above the stand
    glScalef(2.0f, 1.5f, 0.1f); // Scale to resemble a TV screen
    glutSolidCube(1.0);
    glPopMatrix();
    
    glutSwapBuffers(); // Swap the front and back buffers for double buffering
}

// Function to update the display continuously
void idle() {
    glutPostRedisplay(); // Request to redraw the scene
}

int main(int argc, char** argv) {
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffering and depth testing
    glutInitWindowSize(800, 600); // Set the window size
    glutCreateWindow("OpenGL TV Stand Example"); // Create the window with a title

    initOpenGL(); // Call the initialization function

    glutDisplayFunc(display); // Register the display function
    glutIdleFunc(idle); // Register the idle function to update the display continuously

    glutMainLoop(); // Enter the main loop and process events
    return 0; // Exit the program
}
