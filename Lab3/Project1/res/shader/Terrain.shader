#shader vertex
#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	TexCoords = aTexCoords;
	Normal = mat3(transpose(inverse(model))) * aNormal;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}


#shader fragment
#version 330
out vec4 FragColor;
struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS 20
uniform DirLight dirLight;
uniform vec3 viewPos;
uniform PointLight pointLights[NR_POINT_LIGHTS];
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D terrainTexture;
uniform sampler2D terrainAmbient;
uniform sampler2D terrainNormal;


uniform float  shininess;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
void main()
{
	vec3 norm0 = Normal *vec3(texture(terrainNormal, TexCoords));
	vec3 norm = normalize(norm0);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	FragColor = vec4(result, 1.0);
}
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(terrainAmbient, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(terrainTexture, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(terrainAmbient, TexCoords));
	return (ambient + diffuse );
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// combine results
	vec3 ambient = light.ambient * texture(terrainAmbient, TexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(terrainTexture, TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(terrainAmbient, TexCoords).rgb;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse);
}