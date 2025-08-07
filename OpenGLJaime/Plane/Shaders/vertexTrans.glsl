#version 460 core

layout(location = 0) in vec4 vPosition;
//layout(location = 1) in vec4 vColor;


out vec4 color;
uniform float time;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;
uniform float frecuency;
uniform float amplitude;

uniform vec4 outColorRed;
uniform vec4 outColorGreen;
uniform vec4 outColorBlue;


	float F(float x, float z,float amplitude,float phase, float frecuency)
	{
		return amplitude * cos(phase + frecuency * (x * x + z * z));
	}

	
void main()
{
	/*vec4 newPosition = vPosition;
	newPosition.y = height(newPosition.x, newPosition.z, time);
	vec4 finalColor = color;
	finalColor = outColorRed + outColorGreen + outColorBlue;

	if (distance(1.0f, newPosition.x) <= time)
	{
		finalColor.x = cos(time);
		finalColor.y = sin(time);
		finalColor.z = cos(time) + sin(time);
	}
	newPosition.y = 0.3f * cos(time * newPosition.x * newPosition.x ) +
					0.3f * sin(time * newPosition.y * newPosition.y);*/

	vec4 newPosition = vPosition;
	float f = F(newPosition.x, newPosition.z, amplitude, time, frecuency);
	newPosition.y = f;
	color = vec4(clamp(0.7 * F(newPosition.x, newPosition.x, amplitude, time, frecuency), 0.0f, 1.0f), 0.3f, 0.3f, 1.0f);
	


	gl_Position = projection * camera *  accumTrans * newPosition;  //equivale a hacer return gl_Position
}
