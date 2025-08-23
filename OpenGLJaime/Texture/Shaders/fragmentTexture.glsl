#version 460 core

in vec4 color;
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float value;

void main()
{
    vec4 textureLenna = texture(tex0, texCoord);
    vec4 textureKirbo = texture(tex1,texCoord);
    vec4 texelColor = mix(textureLenna,textureKirbo,value);
    fragColor = texelColor;
}
