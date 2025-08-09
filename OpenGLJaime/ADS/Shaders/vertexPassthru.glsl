#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

uniform float time;
uniform float posX,posY;
out vec4 color;
uniform vec4 outColorRed;
uniform vec4 outColorGreen;
uniform vec4 outColorBlue;




void main ()
{  	
	vec4 outPosition = vPosition;
	//outPosition.x = outPosition.x * cos(time);
	//outPosition.y = outPosition.y * sin(time);
	vec4 finalColor = vColor + outColorRed + outColorBlue + outColorGreen;

	
	//color += outColorRed;
	//color += outColorBlue;
	//color += outColorGreen;
	color = finalColor;
	gl_Position = outPosition;  //equivale a hacer return gl_Position
}
