#version 460 core
uniform vec3 eye;

struct Light
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};
struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

in vec4 colorADS;
in vec4 color;
in vec3 normal;
in vec4 newPosition;
in Light light;
in Material material;

out vec4 fragColor;

vec4 ambient(Light L, Material M)
{
	return L.ambient * M.ambient;
}

vec4 diffuse(Light L, Material M, vec3 Normal)
{
	return (max(0.0f, dot(normalize(L.position), normalize(Normal))) * L.diffuse * M.diffuse);
}

vec4 specular(vec3 eye,vec3 vertexPos,Light L,Material M, vec3 Normal,float SH )
{
	vec3 view = normalize(eye) - normalize(vertexPos);
	vec3 RE = normalize(reflect((eye - L.position),Normal));
	vec4 specular = vec4(0.0f,0.0f,0.0f,1.0f);
	if(dot(L.position,view) > 0.0)
	{
		specular = L.specular * M.specular * pow(max(0.0f,dot(view,RE)),SH);
	}
	return specular;
}

void main()
{
    	fragColor = ambient(light, material) + diffuse(light,material,normal) + specular(eye,newPosition.xyz,
		light,material,normal,8.0f);
}
