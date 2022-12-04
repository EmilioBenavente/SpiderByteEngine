#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 VertexColor;

uniform float Offset;

void main()
{
  VertexColor = aPos;
  gl_Position = vec4(aPos.x + Offset, -aPos.y, aPos.z, 1.0);
}
