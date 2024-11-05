#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int WIDTH = 800, HEIGHT = 800;

void drawLogisticMap() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0f);
    glBegin(GL_POINTS);

    // Parameters for the logistic map
    float r, x = 0.5;
    int iterations = 1000, lastIterations = 100;

    for (r = 2.5f; r < 4.0f; r += 0.001f) {
        x = 0.5f;  // Reset x for each r

        // Iterate enough times to reach the "chaotic" region
        for (int i = 0; i < iterations; i++) {
            x = r * x * (1 - x);
            if (i >= iterations - lastIterations) {
                glVertex2f((r - 2.5f) / 1.5f * 2.0f - 1.0f, x * 2.0f - 1.0f);
            }
        }
    }

    glEnd();
    glFlush();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Chaos Theory (Logistic Map)", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        drawLogisticMap();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}