#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Persp;

void main()
{
  gl_Position = Persp * View * Model * vec4(aPos, 1.0);
}
