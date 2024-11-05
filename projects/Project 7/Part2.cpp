// This program is a flyby around the RGB color cube.  One intersting note
// is that because the cube is a convex polyhedron and it is the only thing
// in the scene, we can render it using backface culling only. i.e., there
// is no need for a depth buffer.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// Variables to control keyboard

bool roating = true;
float yAxis = 0;
float angle = 0;
float scale = 0.75f;
float cubesPosition = 0.0f;
bool cubesGoingForward = true;

// The cube has opposite corners at (0,0,0) and (1,1,1), which are black and
// white respectively.  The x-axis is the red gradient, the y-axis is the
// green gradient, and the z-axis is the blue gradient.  The cube's position
// and colors are fixed.
namespace Cube
{

  const int NUM_VERTICES = 8;
  const int NUM_FACES = 6;

  GLint vertices[NUM_VERTICES][3] = {
      {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

  GLint faces[NUM_FACES][4] = {
      {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6}, {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

  GLfloat vertexColors[NUM_VERTICES][3] = {
      {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

  void draw()
  {
    glBegin(GL_QUADS);
    for (int i = 0; i < NUM_FACES; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        glColor3fv((GLfloat *)&vertexColors[faces[i][j]]);
        glVertex3iv((GLint *)&vertices[faces[i][j]]);
      }
    }
    glEnd();
  }
}
// Cube 2 that is floating around the screen
namespace Cube2
{

  const int NUM_VERTICES = 8;
  const int NUM_FACES = 6;

  GLint vertices[NUM_VERTICES][3] = {
      {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

  GLint faces[NUM_FACES][4] = {
      {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6}, {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

  GLfloat vertexColors[NUM_VERTICES][3] = {
      {0.55, 0.75, 0.45},
      {0.65, 0.60, 0.50},
      {0.70, 0.55, 0.80},
      {0.50, 0.80, 0.65},
      {0.60, 0.45, 0.55},
      {0.75, 0.50, 0.60},
      {0.70, 0.85, 0.40},
      {0.45, 0.55, 0.65}};

  void draw()
  {
    glBegin(GL_QUADS);
    for (int i = 0; i < NUM_FACES; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        glColor3fv((GLfloat *)&vertexColors[faces[i][j]]);
        glVertex3iv((GLint *)&vertices[faces[i][j]]);
      }
    }
    glEnd();
  }
}
// Cube 3 that is floating around the screen
namespace Cube3
{

  const int NUM_VERTICES = 8;
  const int NUM_FACES = 6;

  GLint vertices[NUM_VERTICES][3] = {
      {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

  GLint faces[NUM_FACES][4] = {
      {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6}, {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

  GLfloat vertexColors[NUM_VERTICES][3] = {
      {0.47, 0.65, 0.31},
      {0.12, 0.88, 0.54},
      {0.91, 0.26, 0.77},
      {0.38, 0.42, 0.83},
      {0.57, 0.36, 0.98},
      {0.79, 0.04, 0.67},
      {0.14, 0.92, 0.39},
      {0.85, 0.52, 0.13}};

  void draw()
  {
    glBegin(GL_QUADS);
    for (int i = 0; i < NUM_FACES; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        glColor3fv((GLfloat *)&vertexColors[faces[i][j]]);
        glVertex3iv((GLint *)&vertices[faces[i][j]]);
      }
    }
    glEnd();
  }
}
// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotated(angle, 0, 0, 1.0f); // Rotate the scene to create spinining effect.
  glScalef(scale, scale, scale);
  glTranslated(0.0f, yAxis, 0.0f); // Translates the scene so it can move up down left right

  // Draws one of the moving cubes
  glPushMatrix();
  glTranslated(cubesPosition, 1.0f, 0.0f);
  glScalef(0.5, 0.5, 0.5);
  Cube2::draw();
  glPopMatrix();

  // Draws the second moving cube
  glPushMatrix();
  glTranslated(-cubesPosition, -1.0f, 0.0f);
  glScalef(0.5, 0.5, 0.5);
  Cube3::draw();
  glPopMatrix();

  glColor3f(0.5f, 0.5f, 0.5f);

  // Draws the left plan
  glPushMatrix();
  glTranslated(-5.0f, 0.0f, -1.0f);
  glScalef(0.1f, 10.0f, 4.0f);
  glutSolidCube(1);
  glPopMatrix();

  // Draws the right plan
  glPushMatrix();
  glTranslated(6.0f, 0.0f, -1.0f);
  glScalef(0.1f, 10.0f, 4.0f);
  glutSolidCube(1);
  glPopMatrix();

  // Draws the center cube
  glPushMatrix();
  glScalef(0.7, 0.7, 0.7);
  Cube::draw();
  glPopMatrix();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

// We'll be flying around the cube by moving the camera along the orbit of the
// curve u->(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2).  We keep the camera looking
// at the center of the cube (0.5, 0.5, 0.5) and vary the up vector to achieve
// a weird tumbling effect.
void timer(int v)
{
  // if the scene is moving
  if (roating)
  {

    static GLfloat u = 0.0;
    static bool cameraDirection;
    // update the camera position
    u += cameraDirection ? 0.1 : -0.1;
    // change camera direction
    if (u > 10)
      cameraDirection = false;
    if (u < -10)
      cameraDirection = true;
    glLoadIdentity();
    // update camera position
    gluLookAt(0, -2, u, .5, .5, .5, 0, 1, 0);

    // Makes the cubes move back and forth and the camera move back and forth
    if (cubesGoingForward)
    {
      cubesPosition += 0.1;
      // bounces off the wall
      if (cubesPosition > 4)
        cubesGoingForward = false;
    }
    else
    {
      cubesPosition -= 0.1;
      // bounces off the wall
      if (cubesPosition < -4)
        cubesGoingForward = true;
    }
  }

  glutPostRedisplay();
  glutTimerFunc(1000 / 60.0, timer, v);
}

// When the window is reshaped we have to recompute the camera settings to
// match the new window shape.  Set the viewport to (0,0)-(w,h).  Set the
// camera to have a 60 degree vertical field of view, aspect ratio w/h, near
// clipping plane distance 0.5 and far clipping plane distance 40.
void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

// Application specific initialization:  The only thing we really need to do
// is enable back face culling because the only thing in the scene is a cube
// which is a convex polyhedron.
void init()
{
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}
// Keyboard input for switching views
void handleKeys(unsigned char key, int x, int y)
{
  // switch case on key to determine what key is pressed
  switch (key)
  {
  case 'r':
    angle += 1;
    break;
  // Stop the image from spining
  case 'p':
    roating = false;
    break;
  // Start the image spining
  case 'c':
    roating = true;
    break;
  // Move the object up
  case 'u':
    yAxis += 0.3;
    break;
  // Move the object down
  case 'd':
    yAxis -= 0.3;
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
    if (scale > 2)
      scale = 2;
    break;
  }
}

// The usual main for a GLUT application.
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("The RGB Color Cube");
  glutReshapeFunc(reshape);
  glutKeyboardFunc(handleKeys); // Set keyboard function for user input
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
