#version 460 core

in vec4 color;
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float value;

void main()
{
  
    vec4 textureKirbo = texture(tex1,texCoord);
   
    fragColor = textureKirbo;
}
