#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Persp;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
  TexCoords = aTex;
  FragPos = vec3(Model * vec4(aPos, 1.0));
  Normal = mat3(transpose(inverse(Model))) * aNormal;
  gl_Position = Persp * View * Model * vec4(aPos, 1.0);
}
