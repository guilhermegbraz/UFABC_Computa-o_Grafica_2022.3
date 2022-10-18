uniform sampler2D qt_Texture0;
varying vec4 qt_TexCoord0;

layout ( location = 0) in vec4 vPosition;
layout ( location = 1) in vec4 vColors;
out vec4 v2fcolor;

void main (void)
{
    gl_Position = vPosition ; //gl_position -- variavel built-in
    // gl_Position = vPosition*1.1;
    // gl_Position.x = vPosition.x*1.5;
    // vPosition.y = vPosition.y*1.2;
    // gl_Position.xy = vPosition.yx;
    v2fcolor = vColors ;
    v2fcolor.grba = vColors.rgba;
}
