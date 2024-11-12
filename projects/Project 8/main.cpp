#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <cstdlib>

const int WIDTH = 800, HEIGHT = 800;
const int TRAIL_LENGTH = 50;
const int NUM_PARTICLES = 5;

struct Particle {
    float angle;
    float radius;
    float speed;
    float r, g, b;
    std::vector<float> xTrail;
    std::vector<float> yTrail;
    std::vector<float> brightnessTrail;
};

std::vector<Particle> particles;

// Initialize particles with random parameters
void initializeParticles() {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        Particle p;
        p.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;
        p.radius = 0.3f + static_cast<float>(rand()) / RAND_MAX * 0.5f;
        p.speed = 0.01f + static_cast<float>(rand()) / RAND_MAX * 0.05f;
        p.r = static_cast<float>(rand()) / RAND_MAX;
        p.g = static_cast<float>(rand()) / RAND_MAX;
        p.b = static_cast<float>(rand()) / RAND_MAX;

        p.xTrail.resize(TRAIL_LENGTH, 0.0f);
        p.yTrail.resize(TRAIL_LENGTH, 0.0f);
        p.brightnessTrail.resize(TRAIL_LENGTH, 0.0f);
        particles.push_back(p);
    }
}

void updateParticles() {
    for (auto& p : particles) {
        p.angle += p.speed;
        if (p.angle > 2 * M_PI) p.angle -= 2 * M_PI;
        float x = p.radius * cos(p.angle);
        float y = p.radius * sin(p.angle);
        // Shift trail positions
        for (int i = TRAIL_LENGTH - 1; i > 0; --i) {
            p.xTrail[i] = p.xTrail[i - 1];
            p.yTrail[i] = p.yTrail[i - 1];
            p.brightnessTrail[i] = p.brightnessTrail[i - 1] * 0.95f; // Fading effect
        }
        // Update the head of the trail
        p.xTrail[0] = x;
        p.yTrail[0] = y;
        p.brightnessTrail[0] = 1.0f;
    }
}

void drawParticles() {
    for (const auto& p : particles) {
        for (int i = 0; i < TRAIL_LENGTH; ++i) {
            glColor4f(p.r, p.g, p.b, p.brightnessTrail[i]);
            glBegin(GL_POINTS);
            glVertex2f(p.xTrail[i], p.yTrail[i]);
            glEnd();
        }
    }
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Infinite Light Trail", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glewInit();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPointSize(5.0f);

    // Initialize particles with random properties
    initializeParticles();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Update and draw particles
        updateParticles();
        drawParticles();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}