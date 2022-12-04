#version 330 core

uniform vec3 ExtraColor;

in vec3 VertexColor;

out vec4 FragColor;

void main()
{
  FragColor = vec4(VertexColor + ExtraColor, 1.0);
}

