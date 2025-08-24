#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoord;


out vec2 texCoord;
uniform float time;
out vec4 test;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;
uniform float frecuency;
uniform float amplitude;

uniform sampler2D tex0;




	float F(float x, float z,float amplitude,float phase, float frecuency)
	{
		return amplitude * cos(phase + frecuency * (x * x + z * z));
	}

	
void main()
{



	vec4 newPosition = vPosition;
	

	//float f = F(newPosition.x, newPosition.z, amplitude, time, frecuency);
	//newPosition.y = f;
	//color = vec4(clamp(0.7 * F(newPosition.x, newPosition.x, amplitude, time, frecuency), 0.0f, 1.0f), 0.3f, 0.3f, 1.0f);
	texCoord = vTextCoord;
	vec4 HeightMap = texture(tex0,texCoord);
	//test = HeightMap;
	//float L = ((HeightMap.r * 0.2126f) + (HeightMap.g * 0.7152) + (HeightMap.b * 0.0722f));
	float L = (0.299 * pow(HeightMap.r,2) + 0.587 * pow(HeightMap.r, 2) + 0.114 * pow(HeightMap.r,2));
	newPosition.y = L*100;
	gl_Position = projection * camera *  accumTrans * newPosition;  //equivale a hacer return gl_Position
}
