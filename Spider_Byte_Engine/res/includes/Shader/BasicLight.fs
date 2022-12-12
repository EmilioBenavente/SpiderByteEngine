#version 330 core

struct Material_T
{
  sampler2D Diffuse;
  sampler2D Specular;
  float Shininess;
};

struct Light_T
{
  vec3 Position;
  vec3 Color;

  vec3 Ambient;
  vec3 Diffuse;
  vec3 Specular;
};


uniform Material_T Material;
uniform Light_T Light;

uniform vec3 ViewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
  vec3 Result;

  vec3 Ambient = Light.Ambient * vec3(texture(Material.Diffuse, TexCoords));

  vec3 Norm = normalize(Normal);
  vec3 LightDir = normalize(Light.Position - FragPos);
  float Diff = max(dot(Norm, LightDir), 0.0);
  vec3 Diffuse = Light.Diffuse * Diff * vec3(texture(Material.Diffuse, TexCoords)) * Light.Color;

  vec3 ViewDir = normalize(ViewPos - FragPos);
  vec3 ReflectDir = reflect(-LightDir, Norm);
  float Spec = pow(max(dot(ViewDir, ReflectDir), 0.0), Material.Shininess);
  vec3 Specular = Light.Specular * Spec * vec3(texture(Material.Specular, TexCoords));

  Result = (Specular + Diffuse + Ambient);

  FragColor = vec4(Result, 1.0);
}