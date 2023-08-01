#version 330 core

uniform sampler2D UniformTexCoord;
uniform sampler2D UniformTexCoord2;
uniform vec4 UniformColor;

in vec4 VertexColor;
in vec2 TexCoord;
out vec4 FragColor;

void main()
{
	FragColor = mix(texture(UniformTexCoord, TexCoord),
			texture(UniformTexCoord2, TexCoord), 0.4)
			* (VertexColor * UniformColor);
}
