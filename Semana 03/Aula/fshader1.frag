uniform sampler2D qt_Texture0;
varying vec4 qt_TexCoord0;

in vec4 v2fcolor;
out vec4 outfragcolor;

void main(void)
{
    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
    outfragcolor = v2fcolor;
    //media ponderada para escala de cinza, conforme luminancia
    double grayscale = 0.299*v2fcolor.r + 0.587*v2fcolor.g + 0.114*v2fcolor.b;
    outfragcolor = vec4(grayscale ,grayscale ,grayscale ,1);
}

