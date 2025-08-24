#version 460 core

in vec4 color;
in vec2 texCoord;
in vec4 test;
out vec4 fragColor;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float value;

void main()
{
  
    vec4 finalTexture = texture(tex1,texCoord);
   
    fragColor = finalTexture;
}
