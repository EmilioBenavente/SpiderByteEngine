#version 330 core

uniform sampler2D UniformTexCoord;
uniform sampler2D UniformTexCoord2;
uniform vec4 UniformColor;
uniform vec3 LightColor;
uniform vec3 LightPos;
uniform vec3 ViewPos;

in vec4 VertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;


void main()
{
	vec4 ObjectColor = mix(texture(UniformTexCoord, TexCoord),
				texture(UniformTexCoord2, TexCoord), 0.4)
				* (VertexColor * UniformColor);

	float AmbientStrength = 0.1;
	vec3 Ambient = AmbientStrength * LightColor;

	vec3 NormalVector = normalize(Normal);
	vec3 LightDir = normalize(LightPos - FragPos);

	float DiffStrength = max(dot(NormalVector, LightDir), 0.0);
	vec3 Diffuse = DiffStrength * LightColor;

	vec3 ViewDir = normalize(ViewPos - FragPos);
	vec3 ReflectDir = reflect(-LightDir, NormalVector);
	float SpecRadius = pow(max(dot(ViewDir, ReflectDir), 0.0), 256);
	float SpecularStrength = 0.5;
	vec3 Specular = SpecularStrength * SpecRadius * LightColor;

	vec3 Result = (Specular + Diffuse + Ambient) * ObjectColor.xyz;
	FragColor = vec4(Result, 1.0);
}
