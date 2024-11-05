#include <GL/glut.h>
#include <SOIL/SOIL.h>

void rgbColorSelect(int r, int g, int b);

// Function to initialize OpenGL settings
void initOpenGL() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for proper occlusion
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0); // Enable light #0
    glEnable(GL_COLOR_MATERIAL); // Enable color tracking

    //Enable Opacity
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    // Set light properties
    GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, 5.0f, 5.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glClearColor(230/255.0f, 208/255.0f, 177/255.0f, 1.0f); // Set the background color to tan

    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1, 100.0); // Setup the perspective projection

    glMatrixMode(GL_MODELVIEW); // Switch back to the modelview matrix
    glLoadIdentity();

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set texture environment mode
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// Function to draw a shelf with compartments
void drawTvStand() {
    // Draw the main shelf body
    glColor3f(0.15f, 0.0975f, 0); // Brown color
    glPushMatrix();
    glScalef(4.0f, 1.0f, 1.5f); // Scale to resemble a TV stand
    glutSolidCube(1.0); // Draw the main shelf
    glPopMatrix();

    //left foot
    glColor3f(0.0375f, 0.0225f, 0); // Brown color
    glPushMatrix();
    glTranslatef(-2.255f, -0.9f, 0.0f); 
    glScalef(0.1f, 0.2f, 0.2f); 
    glutSolidCube(1.0);
    glPopMatrix();
    
    //right foot
    glPushMatrix();
    glTranslatef(2.255f, -0.9f, 0.0f); 
    glScalef(0.1f, 0.2f, 0.2f); 
    glutSolidCube(1.0);
    glPopMatrix();

    //Black color to draw cubbies and drawer divider

    GLuint texture = SOIL_load_OGL_texture(
        "LeftCubby.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    rgbColorSelect(255,255,255);
    // Draw the left cubby
    glPushMatrix();
    glTranslatef(-1.3f, 0.23f, 0.55f); 
    glScalef(1.25f, 0.4f, 0.5f); // Scale to the desired size
    glBegin(GL_QUADS);
        // Front face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //Middle Cubby
    texture = SOIL_load_OGL_texture(
        "CenterCubby.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    rgbColorSelect(180,180,180);
    // Draw the right cubby
    glPushMatrix();
    glTranslatef(0.0f, 0.23f, 0.55f); 
    glScalef(1.25f, 0.4f, 0.5f); // Scale to the desired size
    glBegin(GL_QUADS);
        // Front face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Draw the right cubby
    rgbColorSelect(0,0,0);
    glPushMatrix();
    glTranslatef(1.3f, 0.23f, 0.51f); 
    glScalef(1.25f, 0.4f, 0.5f); // Scale to the desired size
    glutSolidCube(1.0);
    glPopMatrix();

    rgbColorSelect(0,0,0);
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

    //Left Drawer panel
        rgbColorSelect(255,255,255);
    texture = SOIL_load_OGL_texture(
        "LeftBottom.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Draw the left panel
    glPushMatrix();
    glTranslatef(-1.3f, -0.25f, 0.505f); 
    glScalef(1.0f, 0.3f, 0.5f); 
    glBegin(GL_QUADS);
        // Front face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //Grey/silver color to draw the drawers
    rgbColorSelect(31, 24, 12);
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

    //draw under stand shadow
    glColor4f(0.0f, 0.0f, 0.0f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, -0.90f, 0.1f);
    glScalef(4.5f, 0.1f, 0.001f);
    glutSolidCube(1.0);
    glPopMatrix();

}

void drawGamingConsoles ()
{
    // wii
    rgbColorSelect(120, 120, 120);
    glPushMatrix();
    glTranslatef(.77f, 0.23f, 0.52f);
    glScalef(.15f,.38f, 0.5f);
    glutSolidCube(1);
    glPopMatrix();

    // wii disk slot
    rgbColorSelect(0, 0, 0);
    glPushMatrix();
    glTranslatef(.78f, 0.23f, 0.53f);
    glScalef(.025f,.34f, 0.5f);
    glutSolidCube(1);
    glPopMatrix();

    //sound bar
    rgbColorSelect(7,7,7);
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.45f);
    glScalef(2.5f,.2f, 0.3f);
    glutSolidCube(1);
    glPopMatrix();


    // Draw the TV screen
    rgbColorSelect(0,0,0);
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, -0.5f); // Move above the stand
    glScalef(2.8f, 1.3f, 0.1f); // Scale to resemble a TV screen
    glutSolidCube(1.0);
    glPopMatrix();

    //Draw TV logo
    rgbColorSelect(10,10,10);
    glPushMatrix();
    glTranslatef(0.0f, 0.54f, -0.40f);
    glScalef(0.09f, 0.025f, 0.01f);
    glutSolidCube(1);
    glPopMatrix();

    // Draw TV Shadow
    glColor4f(0.0f, 0.0f, 0.0f, 0.3f);
    glPushMatrix();
    glTranslatef(1.5f, 1.10f, -0.5f);
    glScalef(0.3f, 1.1f, 0.001f);
    glutSolidCube(1.0);
    glPopMatrix();

}

void drawBackground(){
    
    //drawing background trim
    rgbColorSelect(255,255,255);
    GLuint texture = SOIL_load_OGL_texture(
        "WallTrim.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 0.4f);
    glScalef(10.0f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        // Front face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
        glTexCoord2f(10.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
        glTexCoord2f(10.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Drawing Floor
    rgbColorSelect(210, 150, 20);
    texture = SOIL_load_OGL_texture(
        "Floor.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPushMatrix();
    glTranslatef(0.0f, -2.4f, 0.0f);
    glScalef(10.5f, 0.0f, 1.6f);
    glBegin(GL_QUADS);
        // Front face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
        glTexCoord2f(5.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
        glTexCoord2f(5.0f, 1.0f); glVertex3f( 0.5f, -0.5f, -2.2f); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -2.2f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and the depth buffer
    glLoadIdentity(); // Reset the modelview matrix

    // Setup the camera view
    gluLookAt(0.0f, 2.0f, 5.0f,  // Camera position
              0.0f, 0.0f, 0.0f,  // Look at point (origin)
              0.0f, 1.0f, 0.0f); // Up vector

    drawBackground();
    // Draw the TV stand and compartments
    drawTvStand();
    drawGamingConsoles();
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
    glutCreateWindow("OpenGL Part5"); // Create the window with a title

    initOpenGL(); // Call the initialization function

    glutDisplayFunc(display); // Register the display function
    glutIdleFunc(idle); // Register the idle function to update the display continuously

    glutMainLoop(); // Enter the main loop and process events
    return 0; // Exit the program
}

void rgbColorSelect(int r, int g, int b)
{
    GLfloat red = r/255.0f;
    GLfloat green = g/255.0f;
    GLfloat blue = b/255.0f;
    glColor3f(red, green, blue);
}
