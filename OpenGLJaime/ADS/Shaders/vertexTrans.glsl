#version 460 core

layout(location = 0) in vec4 vPosition;
//layout(location = 1) in vec4 vColor;


out vec4 color;
out vec4 colorADS;
uniform float time;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;
uniform vec3 eye;
uniform float frecuency;
uniform float amplitude;

//uniform vec4 outColorRed;
//uniform vec4 outColorGreen;
//uniform vec4 outColorBlue;


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

	vec4 ambient(Light L, Material M)
	{
		return L.ambient * M.ambient;
	}
	vec4 diffuse(Light L, Material M, vec3 Normal)
	{
		return (max(0.0f, dot(normalize(L.position), normalize(Normal))) * L.diffuse * M.diffuse);
		//return L.diffuse * M.diffuse * (dot(normalize(L.position),normalize(Normal)));
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

	//vec3 Normal = vec3(0.0, 1.0f, 0);
	Light light;
	light.ambient = vec4(1.0f, 0.01f, 1.0f, 1.0f);
	light.diffuse = vec4(1.0f, 0.1f, 1.0f, 1.0f);
	light.position = vec3(0.0f, 2.0f, 1.0f);
	light.specular = vec4(0.0f,0.5f,0.0f,1.0f);
	Material material;
	material.ambient = vec4(0.01f, 0.01f, 1.0f, 1.0f);
	material.diffuse = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = vec4(0.0f,0.5f,0.0f,1.0f);

	vec4 finalColor = vec4(1.0f,1.0f,1.0f,1.0f);
	vec4 newPosition = vPosition;
	vec3 vertexPos = vec3(newPosition.x,newPosition.y,newPosition.z);
	
		
//	if(distance(vec4(0.0f,0.0f,0.0f,1.0),newPosition) <= time)
//	{
//		finalColor = vec4(1.0f,1.0f,1.0f,1.0f);
//		
//	}

	/*vec4 newPosition = vPosition;
	newPosition.y = height(newPosition.x, newPosition.z, time);
	if (distance(1.0f, newPosition.x) <= time)
	{
		finalColor.x = cos(time);
		finalColor.y = sin(time);
		finalColor.z = cos(time) + sin(time);

	}
	*/
//	newPosition.y = 0.3f * cos(time * newPosition.x * newPosition.x ) +
//					0.3f * sin(time * newPosition.y * newPosition.y);
	float f = F(newPosition.x, newPosition.z, amplitude, time, frecuency);
	newPosition.y = f;
	vec4 colorLow = vec4(0.0f,0.0f,0.0f,1.0f);
	vec4 colorMid = vec4(0.0f,0.0f,0.0f,1.0f);
	vec4 colorHight = vec4(0.0f,0.0f,0.0f,1.0f);
	
	if(f <= -0.125f)
		colorLow = vec4(0.0, 0.0, 0.0, 1.0);
	else if (f <= 0.0)
		 colorMid = vec4(0.5, 0.5, 0.5, 1.0);
	else if (f <= 0.125f)
		vec4 colorHight = vec4(1.0, 1.0, 1.0, 1.0);

	finalColor = colorLow + colorMid + colorHight;



	//color = vec4(clamp(0.7 * F(newPosition.x, newPosition.x, amplitude, time, frecuency), 0.0f, 1.0f), 0.3f, 0.3f, 1.0f);
	color = finalColor;
	vec3 Normal = NormalCalculate(newPosition.x,newPosition.z,amplitude,time,frecuency);
	mat4 matForNormals = transpose(inverse(camera*accumTrans)); //Matriz solo para las normales
	Normal = normalize(matForNormals * vec4(Normal,1.0)).xyz;
	newPosition = camera *  accumTrans * newPosition;
	colorADS = ambient(light, material) + diffuse(light,material,Normal) + specular(eye,newPosition.xyz,
		light,material,Normal,8.0f);


	gl_Position = projection * newPosition;  //equivale a hacer return gl_Position
}
