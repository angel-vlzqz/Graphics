#version 330 core
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
  FragColor = texture(ourTexture, TexCoord); // TexCoord is a vec2
}
