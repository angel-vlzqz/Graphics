// This application is a trivial illustration of texture mapping.  It draws
// several triangles, each with a texture mapped on to it.  The same texture
// is used for each triangle, but the mappings vary quite a bit so it looks as
// if each triangle has a different texture.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

// Define a 2 x 2 red and yellow checkered pattern using RGB colors.
#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}
GLubyte texture[][3] = {
    red,
    yellow,
    yellow,
    red,
};

bool spining = true;
float angle = 0.0f;
float yAxis = 0.0f;
float xAxis = 0.0f;
float scale = 1.0f;

// Fixes up camera and remaps texture when window reshaped.
void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80, GLfloat(width) / height, 1, 40);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D,
               0,                // level 0
               3,                // use only R, G, and B components
               2, 2,             // texture has 2x2 texels
               0,                // no border
               GL_RGB,           // texels are in RGB format
               GL_UNSIGNED_BYTE, // color components are unsigned bytes
               texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Draws three textured triangles.  Each triangle uses the same texture,
// but the mappings of texture coordinates to vertex coordinates is
// different in each triangle.
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glTranslated(xAxis, yAxis, 0.0f); // Translates the object so it can move up down left right
  glRotated(angle, 0, 0, 1.0f);     // Rotate the object to create spinining effect.
  glScalef(scale, scale, 1);        // Scale the object so it zooms in and out
  glBegin(GL_TRIANGLES);
  glTexCoord2f(0.5, 1.0);
  glVertex2f(-3, 3);
  glTexCoord2f(0.0, 0.0);
  glVertex2f(-3, 0);
  glTexCoord2f(1.0, 0.0);
  glVertex2f(0, 0);

  glTexCoord2f(4, 8);
  glVertex2f(3, 3);
  glTexCoord2f(0.0, 0.0);
  glVertex2f(0, 0);
  glTexCoord2f(8, 0.0);
  glVertex2f(3, 0);

  glTexCoord2f(5, 5);
  glVertex2f(0, 0);
  glTexCoord2f(0.0, 0.0);
  glVertex2f(-1.5, -3);
  glTexCoord2f(4, 0.0);
  glVertex2f(1.5, -3);
  glEnd();
  glPopMatrix();
  glFlush();
}
// Keyboard input for switching views
void handleKeys(unsigned char key, int x, int y)
{
  // switch case on key to determine what key is pressed
  switch (key)
  {
  // Stop the image from spining
  case 'p':
    spining = false;
    break;
  // Start the image spining
  case 'c':
    spining = true;
    break;
  // Move the object up
  case 'u':
    yAxis += 0.5;
    break;
  // Move the object down
  case 'd':
    yAxis -= 0.5;
    break;
  // Move the object to the left
  case 'l':
    xAxis -= 0.5;
    break;
  // Move the object to the right
  case 'r':
    xAxis += 0.5;
    break;
  // Zoom out on the object
  case '-':
    scale -= 0.1;
    if (scale < 0)
      scale = 0;
    break;
  // Zoom in on the object
  case '=':
  case '+':
    scale += 0.1;
    if (scale > 10)
      scale = 10;
    break;
  }
}

// animate function to create the spinning effect on the object
void animate(int value)
{
  // increase the angle if the object is spining
  if (spining)
    angle++;
  // redisplay the screen
  glutPostRedisplay();
  // call animate again in 10 miliseconds
  glutTimerFunc(10, animate, 0);
}

// Initializes GLUT and enters the main loop.
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(520, 390);
  glutCreateWindow("Textured Triangles");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(handleKeys);  // Set keyboard function for user input
  glutTimerFunc(10, animate, 0); // call animate in 10 miliseconds
  glutMainLoop();
}
