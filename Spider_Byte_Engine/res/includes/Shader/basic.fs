#version 330 core

uniform vec3 ExtraColor;
uniform sampler2D Texture;
uniform sampler2D Texture2;
uniform float MixVal;

in vec3 VertexColor;
in vec2 TexCoord;

out vec4 FragColor;

void main()
{
  FragColor = mix(texture(Texture, TexCoord), texture(Texture2, TexCoord), MixVal) *
  vec4(ExtraColor + VertexColor, 1.0);
}
