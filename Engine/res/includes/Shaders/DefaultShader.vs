#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec4 VertexColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	VertexColor = Projection * vec4(aColor, 1.0);
	vec4 TexCoordA = Projection * View * Model * vec4(aTex, 1.0, 1.0);
	TexCoord = vec2(TexCoordA.x, TexCoordA.y);
	Normal = mat3(transpose(inverse(Model))) * aNormal;
	//TexCoord = aTex;
	FragPos = vec3(Model * vec4(aPos, 1.0));
	gl_Position = Projection * View * Model * vec4(aPos, 1.0);
}
