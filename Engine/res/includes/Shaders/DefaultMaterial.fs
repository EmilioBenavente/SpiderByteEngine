#version 330 core

uniform sampler2D UniformTexCoord;
uniform sampler2D UniformTexCoord2;
uniform vec4 UniformColor;
uniform vec3 LightPos;
uniform vec3 ViewPos;

in vec4 VertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct MaterialStruct
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Shininess;
};
uniform MaterialStruct Material;

struct LightStruct
{
	vec3 Position;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};
uniform LightStruct Light;


void main()
{
	vec4 ObjectColor = mix(texture(UniformTexCoord, TexCoord),
				texture(UniformTexCoord2, TexCoord), 0.4)
				* (VertexColor * UniformColor);

	vec3 Ambient = Light.Ambient * Material.Ambient;

	vec3 NormalVector = normalize(Normal);
	vec3 LightDir = normalize(Light.Position - FragPos);

	float DiffStrength = max(dot(NormalVector, LightDir), 0.0);
	vec3 Diffuse = Light.Diffuse * (DiffStrength * Material.Diffuse);

	vec3 ViewDir = normalize(ViewPos - FragPos);
	vec3 ReflectDir = reflect(-LightDir, NormalVector);
	float SpecRadius = pow(max(dot(ViewDir, ReflectDir), 0.0), 256);
	vec3 Specular = Light.Specular * (Material.Shininess * SpecRadius * Material.Specular);

	vec3 Result = (Specular + Diffuse + Ambient) * ObjectColor.xyz;
	FragColor = vec4(Result, 1.0);
}
