#version 400

layout ( location = 0) in vec4 vPosition;
layout ( location = 1) in vec4 vColors;

uniform vec4 vColor;
uniform int solid_color;

uniform float scaling;
uniform vec4 translation;

out vec4 v2fcolor;

void main(void)
{
    //gl_Position = vPosition;
    gl_Position = (vPosition * vec4(scaling, scaling, scaling, 1)) + translation ;

    if(solid_color == 1){
        v2fcolor = vColor;
    }


    else{
        v2fcolor = vColors;
    }


}
