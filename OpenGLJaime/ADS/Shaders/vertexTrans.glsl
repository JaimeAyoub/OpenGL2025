#version 460 core

layout(location = 0) in vec4 vPosition;
//layout(location = 1) in vec4 vColor;


out vec4 color;
out vec4 colorADS;
uniform float time;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;
uniform float frecuency;
uniform float amplitude;

uniform vec4 outColorRed;
uniform vec4 outColorGreen;
uniform vec4 outColorBlue;


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

	float F(float x, float z,float amplitude,float phase, float frecuency)
	{
		return amplitude * cos(phase + frecuency * (x * x + z * z));
	}

	vec4 ambient(Light L, Material M)
	{
		return L.ambient * M.ambient;
	}
	vec4 diffuse(Light L, Material M, vec3 Normal)
	{
		return (max(0.0f, dot(normalize(L.position), normalize(Normal))) * L.diffuse * M.diffuse);
		//return L.diffuse * M.diffuse * (dot(normalize(L.position),normalize(Normal)));
	}
	
	

	
void main()
{

	vec3 Normal = vec3(0.0, cos(radians(45)), sin(radians(45)));
	Light light;
	light.ambient = vec4(1.0f, 0.01f, 1.0f, 1.0f);
	light.diffuse = vec4(1.0f, 0.1f, 1.0f, 1.0f);
	light.position = vec3(0.0f, 1.0f, 0.0f);
	Material material;
	material.ambient = vec4(0.01f, 0.01f, 1.0f, 1.0f);
	material.diffuse = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	vec4 finalColor = color;
	vec4 newPosition = vPosition;

	/*vec4 newPosition = vPosition;
	newPosition.y = height(newPosition.x, newPosition.z, time);
	finalColor = outColorRed + outColorGreen + outColorBlue;

	if (distance(1.0f, newPosition.x) <= time)
	{
		finalColor.x = cos(time);
		finalColor.y = sin(time);
		finalColor.z = cos(time) + sin(time);
	}
	newPosition.y = 0.3f * cos(time * newPosition.x * newPosition.x ) +
					0.3f * sin(time * newPosition.y * newPosition.y);*/

	/*if (distance(vec4(0.0f,0.0f,0.0f,1.0f), newPosition) <= time)
	{
		finalColor.x = cos(time);
		finalColor.y = sin(time);
		finalColor.z = cos(time) + sin(time);
	}*/
	//float f = F(newPosition.x, newPosition.z, amplitude, time, frecuency);
	//newPosition.y = f;
	//color = vec4(clamp(0.7 * F(newPosition.x, newPosition.x, amplitude, time, frecuency), 0.0f, 1.0f), 0.3f, 0.3f, 1.0f);
	
	colorADS = ambient(light, material) + diffuse(light,material,Normal);
	gl_Position = projection * camera *  accumTrans * newPosition;  //equivale a hacer return gl_Position
}
