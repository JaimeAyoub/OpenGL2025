#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoord;


out vec2 texCoord;
out vec4 newPosition;
out mat4 accTrans;
out mat4 camer;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;




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




void main()
{

	light.ambient = vec4(0.3f, 0.3f, 0.3f, 0.3f);
	light.diffuse = vec4(0.3f, 0.3f, 0.3f, 0.3f);
	light.position = vec3(0.0f, 3.0f, 1.5f);
	light.specular = vec4(0.3f, 0.3f, 0.3f, 0.3f);



	newPosition = vPosition;

	texCoord = vTextCoord;
	camer = camera;
	accTrans = accumTrans;





	gl_Position = projection * camera * accumTrans * newPosition;  //equivale a hacer return gl_Position
}
