#include <GLUT/glut.h>
#include <string>
#include <iostream>

#define GL_SILENCE_DEPRECATION

float currentTime = 0.0f;
GLuint shaderProgram;
// Vertex shader
const char* vertexShaderSource = 
    "#version 120\n"
    "attribute vec2 aPos;\n"
    "void main() {\n"
    "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
    "}\n";
// Fragment shader
const char* fragmentShaderSource = 
    "#version 120\n"
    "uniform float time;\n"
    "\n"
    "const float PI = 3.14159265359;\n"
    "\n"
    "void main() {\n"
    "    vec2 pos = gl_FragCoord.xy / vec2(800, 800) * 2.0 - 1.0;\n"
    "    \n"
    "    float wave = sin(pos.x * 5.0 + time) * cos(pos.y * 5.0 + time) * 0.5;\n"
    "    wave += sin(length(pos) * 3.0 - time) * 0.3;\n"
    "    \n"
    "    vec3 color;\n"
    "    color.r = 0.5 + 0.5 * sin(wave + time);\n"
    "    color.g = 0.5 + 0.5 * sin(wave + time + 2.0 * PI / 3.0);\n"
    "    color.b = 0.5 + 0.5 * sin(wave + time + 4.0 * PI / 3.0);\n"
    "    \n"
    "    gl_FragColor = vec4(color, 1.0);\n"
    "}\n";
// Quad vertices
const float vertices[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f
};
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    // Check compilation status
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
    }
    return shader;
}
void initShaders() {
    // Create and compile shaders
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    // Create and link shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check linking status
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
    }
    // Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // Use the shader program
    glUseProgram(shaderProgram);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Update time uniform
    GLint timeLocation = glGetUniformLocation(shaderProgram, "time");
    glUniform1f(timeLocation, currentTime);
    // Draw fullscreen quad
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glutSwapBuffers();
}
void update(int value) {
    currentTime += 0.05f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Wave Pattern Demo");
    init();
    initShaders();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
