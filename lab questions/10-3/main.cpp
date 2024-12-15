#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Simple vertex and fragment shaders for environment mapping
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPos;

out vec3 Normal;
out vec3 WorldPos;
out vec3 EyePos;

void main()
{
    vec4 worldPosition = model * vec4(aPos, 1.0);
    WorldPos = worldPosition.xyz;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    EyePos = cameraPos;
    gl_Position = projection * view * worldPosition;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 Normal;
in vec3 WorldPos;
in vec3 EyePos;

out vec4 FragColor;

uniform samplerCube skybox;
uniform float reflectivity;

void main()
{
    vec3 I = normalize(WorldPos - EyePos);
    vec3 R = reflect(I, normalize(Normal));
    vec3 envColor = texture(skybox, R).rgb;
    vec3 baseColor = vec3(0.8, 0.8, 0.8);
    vec3 finalColor = mix(baseColor, envColor, reflectivity);
    FragColor = vec4(finalColor, 1.0);
}
)";

// Utility function to check shader compilation/linking errors.
void checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "| ERROR::SHADER-COMPILATION of type: " << type << "\n" 
                      << infoLog << "\n -- --------------------------------------------------- -- " 
                      << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "| ERROR::PROGRAM-LINKING of type: " << type << "\n" 
                      << infoLog << "\n -- --------------------------------------------------- -- " 
                      << std::endl;
        }
    }
}

// Load a cubemap texture from 6 individual texture faces
GLuint loadCubeMap(std::vector<std::string> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;
            
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
            return 0;
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    return textureID;
}

// Generate a sphere mesh (positions and normals)
void createSphere(float radius, unsigned int sectorCount, unsigned int stackCount,
                  std::vector<float> &vertices, std::vector<unsigned int> &indices)
{
    float x, y, z, xy;                               // vertex position
    float nx, ny, nz;                                // vertex normal
    float lengthInv = 1.0f / radius;                 // normalizing
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for (unsigned int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI/2 - (float)i * stackStep;   // from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);              // r * cos(u)
        z = radius * sinf(stackAngle);               // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (unsigned int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;            // from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
        }
    }

    // indices
    // k1--k1+1
    // |    |
    // k2--k2+1
    unsigned int k1, k2;
    for (unsigned int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1); 
        k2 = k1 + sectorCount + 1; 

        for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount-1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

int main()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    // Create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Environment Mapping Demo", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Build and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkCompileErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Load cubemap
    std::vector<std::string> faces
    {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };
    GLuint cubeMapTexture = loadCubeMap(faces);
    if (cubeMapTexture == 0) {
        std::cerr << "Failed to load cubemap texture.\n";
        return -1;
    }

    // Create sphere geometry
    std::vector<float> sphereVertices;
    std::vector<unsigned int> sphereIndices;
    createSphere(1.0f, 36, 18, sphereVertices, sphereIndices);

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), &sphereVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(unsigned int), &sphereIndices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Simple camera matrices
    float fov = 45.0f;
    float aspect = 800.0f / 600.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    auto radians = [](float deg) { return deg * (M_PI/180.0f); };

    auto perspective = [&](float fovy, float aspect, float near, float far) {
        float tanHalfFovy = tanf(fovy / 2.0f);
        float mat[16] = {0};
        mat[0] = 1.0f / (aspect * tanHalfFovy);
        mat[5] = 1.0f / (tanHalfFovy);
        mat[10] = -(far + near) / (far - near);
        mat[11] = -1.0f;
        mat[14] = -(2.0f * far * near) / (far - near);
        // We will upload this directly as uniform
        std::vector<float> m(mat, mat+16);
        return m;
    };

    auto lookAt = [&](float eyeX, float eyeY, float eyeZ,
                      float centerX, float centerY, float centerZ,
                      float upX, float upY, float upZ) {
        float fX = centerX - eyeX;
        float fY = centerY - eyeY;
        float fZ = centerZ - eyeZ;
        float lenF = sqrtf(fX*fX + fY*fY + fZ*fZ);
        fX /= lenF; fY /= lenF; fZ /= lenF;

        float upLen = sqrtf(upX*upX + upY*upY + upZ*upZ);
        upX /= upLen; upY /= upLen; upZ /= upLen;

        // s = f x up
        float sX = fY*upZ - fZ*upY;
        float sY = fZ*upX - fX*upZ;
        float sZ = fX*upY - fY*upX;
        float lenS = sqrtf(sX*sX + sY*sY + sZ*sZ);
        sX /= lenS; sY /= lenS; sZ /= lenS;
        
        // u = s x f
        float uX = sY*fZ - sZ*fY;
        float uY = sZ*fX - sX*fZ;
        float uZ = sX*fY - sY*fX;

        float mat[16] = { sX, uX, -fX, 0,
                          sY, uY, -fY, 0,
                          sZ, uZ, -fZ, 0,
                          0,   0,   0,   1 };

        // translate
        mat[12] = -(sX*eyeX + sY*eyeY + sZ*eyeZ);
        mat[13] = -(uX*eyeX + uY*eyeY + uZ*eyeZ);
        mat[14] = fX*eyeX + fY*eyeY + fZ*eyeZ;

        std::vector<float> m(mat, mat+16);
        return m;
    };

    auto multiplyMat4 = [&](const std::vector<float>& A, const std::vector<float>& B) {
        std::vector<float> C(16, 0.0f);
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 4; k++)
                    C[i*4+j] += A[i*4+k]*B[k*4+j];
        return C;
    };

    // Camera and transforms
    float cameraPos[3] = {0.0f, 0.0f, 3.0f};
    auto proj = perspective(radians(fov), aspect, nearPlane, farPlane);
    auto view = lookAt(cameraPos[0], cameraPos[1], cameraPos[2],
                       0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f);

    // Identity model matrix
    std::vector<float> model(16, 0.0f);
    model[0] = 1.0f; model[5] = 1.0f; model[10] = 1.0f; model[15] = 1.0f;

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Clear
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use shader
        glUseProgram(shaderProgram);

        // Set uniforms
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
        GLint cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
        GLint reflectLoc = glGetUniformLocation(shaderProgram, "reflectivity");

        glUniform3fv(cameraPosLoc, 1, cameraPos);
        glUniform1f(reflectLoc, 0.9f);  // high reflectivity

        // Upload matrices
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0]);

        // Bind cube map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
        GLint skyboxLoc = glGetUniformLocation(shaderProgram, "skybox");
        glUniform1i(skyboxLoc, 0);

        // Render sphere
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, (GLsizei)sphereIndices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}