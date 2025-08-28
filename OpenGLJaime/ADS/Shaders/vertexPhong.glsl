#version 460 core

layout(location = 0) in vec4 vPosition;


out vec4 color;
out vec4 colorADS;
out vec4 newPosition;


uniform float time;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;
uniform vec3 eye;
uniform float frecuency;
uniform float amplitude;



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
out Light light;
out Material material;


	float F(float x, float z,float amplitude,float phase, float frecuency)
	{
		return amplitude * cos(phase + frecuency * (x * x + z * z));
	}
	float DF(float a, float b,float amplitude,float phase, float frecuency)
	{
		return - sin(phase + frecuency *(a*a + b*b) * (2.0f + 2.0f * a));
	}

	vec3 NormalCalculate(float x, float z,float amplitude,float phase, float frecuency)
	{

	return normalize(
		 vec3(
		DF(x,z,frecuency,phase,amplitude),
		1.0f,
		DF(z,x,frecuency,phase,amplitude)
		));
	}
	out vec3 normal;

	
	

	
void main()
{


	light.ambient = vec4(1.0f, 0.01f, 1.0f, 1.0f);
	light.diffuse = vec4(1.0f, 0.1f, 1.0f, 1.0f);
	light.position = vec3(0.0f, 2.0f, 1.0f);
	light.specular = vec4(0.0f,0.5f,0.0f,1.0f);

	material.ambient = vec4(0.01f, 0.01f, 1.0f, 1.0f);
	material.diffuse = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = vec4(0.0f,0.5f,0.0f,1.0f);

	newPosition = vPosition;
		

	float f = F(newPosition.x, newPosition.z, amplitude, time, frecuency);
	newPosition.y = f;


	normal = NormalCalculate(newPosition.x,newPosition.z,amplitude,time,frecuency);

	mat4 matForNormals = transpose(inverse(camera*accumTrans)); //Matriz solo para las normales
	normal = normalize(matForNormals * vec4(normal,1.0)).xyz;
	newPosition = camera *  accumTrans * newPosition;
	


	gl_Position = projection * newPosition;  //equivale a hacer return gl_Position
}
