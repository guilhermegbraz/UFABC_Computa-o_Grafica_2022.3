#version 400

layout ( location = 0) in vec4 vPosition;
layout ( location = 1) in vec4 vColors;

uniform vec4 vColor;
uniform int solid_color;

out vec4 v2fcolor;

void main(void)
{
    gl_Position = vPosition;

    if(solid_color == 1)
        v2fcolor = vColor;
    else
        v2fcolor = vColors;

}
