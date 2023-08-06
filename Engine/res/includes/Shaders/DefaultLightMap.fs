#version 330 core

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
	sampler2D Diffuse;
	sampler2D Specular;
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
//uniform LightStruct Light;


struct DirectionLightStruct
{
	vec3 Direction;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};
//uniform DirectionLightStruct Light;

struct PointLightStruct
{
	vec3 Position;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	float Constant;
	float Linear;
	float Quadratic;
};
//uniform PointLightStruct Light;

struct FlashlightStruct
{
	vec3 Position;
	vec3 Direction;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	float Constant;
	float Linear;
	float Quadratic;

	float OuterCutoff;
	float InnerCutoff;
};
uniform FlashlightStruct Light;



void main()
{
	vec4 ObjectColor = (VertexColor * UniformColor);

	float Distance = length(Light.Position - FragPos);
	float Attenuation = 1.0 / (Light.Constant + Light.Linear * Distance +
				Light.Quadratic * (Distance * Distance));
	vec3 Ambient = Light.Ambient * vec3(texture(Material.Diffuse, TexCoord));
	Ambient *= Attenuation;

	vec3 NormalVector = normalize(Normal);
	vec3 LightDir = normalize(Light.Position - FragPos);

	float DiffStrength = max(dot(NormalVector, LightDir), 0.0);
	vec3 Diffuse = Light.Diffuse * DiffStrength * vec3(texture(Material.Diffuse, TexCoord));
	Diffuse *= Attenuation;

	vec3 ViewDir = normalize(ViewPos - FragPos);
	vec3 ReflectDir = reflect(-Light.Direction, NormalVector);
	float SpecRadius = pow(max(dot(ViewDir, ReflectDir), 0.0), Material.Shininess);
	vec3 Specular = (Light.Specular * SpecRadius)
				* vec3(texture(Material.Specular, TexCoord));
	Specular *= Attenuation;

	vec3 Result = vec3(0.0);
	float Theta = dot(LightDir, normalize(-Light.Direction));
	float Epsilon = Light.InnerCutoff - Light.OuterCutoff;
	float Intensity = clamp((Theta - Light.OuterCutoff) / Epsilon, 0.0, 1.0);
	if(Theta > Light.OuterCutoff)
	{
		Diffuse *= Intensity;
		Specular *= Intensity;
		Result = (Specular + Diffuse + Ambient)
		 * ObjectColor.xyz;
	}
	else
	{
		Result = Light.Ambient * ObjectColor.xyz;
	}
	FragColor = vec4(Result, 1.0);
}
