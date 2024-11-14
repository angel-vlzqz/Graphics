#include <GLUT/glut.h>
#include <cmath>
#include <vector>

const int NUM_TRAILS = 5;
const int TRAIL_LENGTH = 50;

struct Point {
    float x, y, z;
    float r, g, b;
};

struct Trail {
    std::vector<Point> points;
    float speed;
    float phase;
    float radius;
};

std::vector<Trail> trails;
float angle = 0.0f;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

    // Initialize trails with different properties
    for (int i = 0; i < NUM_TRAILS; i++) {
        Trail trail;
        trail.speed = 0.5f + (float)rand() / RAND_MAX * 2.0f;
        trail.phase = (float)rand() / RAND_MAX * M_PI * 2;
        trail.radius = 0.5f + (float)rand() / RAND_MAX * 1.0f;
        
        // Initialize with empty points
        for (int j = 0; j < TRAIL_LENGTH; j++) {
            Point p = {0, 0, 0, 
                      0.5f + 0.5f * sin(i * 2.1f),
                      0.5f + 0.5f * sin(i * 3.2f),
                      0.5f + 0.5f * sin(i * 4.3f)};
            trail.points.push_back(p);
        }
        trails.push_back(trail);
    }
}

void updateTrail(Trail& trail, float time) {
    // Calculate new head position using parametric equations
    Point newPoint;
    float t = time * trail.speed + trail.phase;
    newPoint.x = trail.radius * sin(t * 1.1f) * cos(t * 0.7f);
    newPoint.y = trail.radius * sin(t * 0.8f);
    newPoint.z = trail.radius * cos(t * 1.3f) * sin(t * 0.9f);
    
    // Shift all points back and add new point at front
    for (int i = TRAIL_LENGTH - 1; i > 0; i--) {
        trail.points[i] = trail.points[i - 1];
    }
    newPoint.r = trail.points[0].r;
    newPoint.g = trail.points[0].g;
    newPoint.b = trail.points[0].b;
    trail.points[0] = newPoint;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(3.0f, 2.0f, 3.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
    
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Draw each trail
    for (auto& trail : trails) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < TRAIL_LENGTH; i++) {
            float alpha = 1.0f - (float)i / TRAIL_LENGTH;
            glColor4f(trail.points[i].r, trail.points[i].g, trail.points[i].b, alpha);
            glVertex3f(trail.points[i].x, trail.points[i].y, trail.points[i].z);
        }
        glEnd();
    }
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w/h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
    angle += 0.5f;
    
    for (auto& trail : trails) {
        updateTrail(trail, angle * 0.05f);
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Light Trails");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}
