#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 Persp;
uniform mat4 View;
uniform mat4 Model;

out vec3 VertexColor;
out vec2 TexCoord;

void main()
{
  VertexColor = aPos;
  TexCoord = aTex;
  gl_Position = Persp * Model * vec4(aPos, 1.0);
  //gl_Position = Persp * View * Model * vec4(aPos, 1.0);
}
