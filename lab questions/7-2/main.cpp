#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include "include/stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

// Set up your vertices and texture coordinates
float vertices[] = {
  // positions        // texture coords
  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
  -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[] = {  // define the order of the vertices
  0, 1, 3,
  1, 2, 3
};

// Load texture image using stb_image
int width, height, nrChannels;
unsigned char *data = stbi_load("path/to/texture.jpg", &width, &height, &nrChannels, 0);

unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(data);

// Set texture parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// Prepare to draw
glUseProgram(shaderProgram);
glBindTexture(GL_TEXTURE_2D, texture);
glBindVertexArray(VAO);

// Draw elements
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
