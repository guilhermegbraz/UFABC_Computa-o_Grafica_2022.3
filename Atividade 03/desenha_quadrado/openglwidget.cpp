#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void OpenGLWidget::initializeGL()
{
   initializeOpenGLFunctions();
   glClearColor(0.2,0.671,0.976,1);

   qDebug("OpenGL Version: %s",glGetString(GL_VERSION));
   qDebug("GLSL Version: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));

   createShaders();
   createVBOs();

#if BLINK
   QObject::connect(&timer, &QTimer::timeout,[&](){this->update();});
   timer.start (200) ;
#endif
}

void OpenGLWidget::resizeGL(int w, int h)
{
}

void OpenGLWidget::paintGL()
{
#if BLINK
    blinkFlag =! blinkFlag;
      if (blinkFlag)
          glClearColor (1, 1, 1, 1);
      else
       glClearColor (0, 0, 0, 1);
#endif
      glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWidget::toggleDarkMode(bool changeToDarkMode)
{
    makeCurrent();
    if(changeToDarkMode)
        glClearColor(0,0,0,1);
    else
        glClearColor(1,1,1,1);
    update();
}

void OpenGLWidget :: drawnSolidRectangle() {
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 1, 0, 0.8, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoRectangle);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}

void OpenGLWidget::createShaders(){
    makeCurrent();
    destroyShaders();
    QFile vs(":/shaders/vshader1.glsl");
    QFile fs(":/shaders/fshader1.glsl");
    if(!vs.open(QFile::ReadOnly | QFile::Text)) return;//inserir mensagem de erro
    if(!fs.open(QFile::ReadOnly | QFile::Text)) return;//inserir mensagem de erro

    auto byteArrayVs{vs.readAll()};
    auto byteArrayFs{fs.readAll()};
    const char *c_strVs{byteArrayVs};
    const char *c_strFs{byteArrayFs};

    vs.close();
    fs.close();
    GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &c_strVs,0);
    glCompileShader(vertexShader);
    GLint isCompiled{0};

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength{0};
        glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader,maxLength,&maxLength,&infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteShader(vertexShader);
        return;
    }
    GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader,1,&c_strFs,0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength{0};
        glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader,maxLength,&maxLength,&infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    GLint isLinked{0};
    glGetProgramiv(shaderProgram,GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength{0};
        glGetProgramiv(shaderProgram,GL_INFO_LOG_LENGTH,&maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram,maxLength,&maxLength, &infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }
    glDetachShader(shaderProgram,vertexShader);
    glDetachShader(shaderProgram,fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void OpenGLWidget::destroyShaders()
{
    makeCurrent();
    glDeleteProgram(shaderProgram);
}

void OpenGLWidget:: createVBOs() {
    makeCurrent();
    destroyVBOs();

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;

    vertices.resize(4);
    colors.resize(4);
    indices.resize(4);

    float posx{0.3f};
    float posy{0.3f};
    float offSet{0.5f};

    vertices[0] = QVector4D(posx - offSet, posy - offSet, 0, 1);
    vertices[1] = QVector4D(posx + offSet, posy - offSet, 0, 1);
    vertices[2] = QVector4D(posx - offSet, posy + offSet, 0, 1);
    vertices[3] = QVector4D(posx + offSet, posy + offSet, 0, 1);


    colors[0] = QVector4D(1, 0, 0, 1);
    colors[1] = QVector4D(0, 1, 0, 1);
    colors[2] = QVector4D(0, 0, 1, 1);
    colors[3] = QVector4D(1, 1, 0, 1);

    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 2; indices[4] = 3; indices[5] = 0;

    glGenBuffers(1, &vaoRectangle);
    glBindVertexArray(vaoRectangle);

    glGenBuffers(1, &vboVerticesRectangle);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesRectangle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vboColorsRectangle);
    glBindBuffer(GL_ARRAY_BUFFER, vboColorsRectangle);
    glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(QVector4D), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &eboIndicesRectangle);
    glBindBuffer(GL_ARRAY_BUFFER, eboIndicesRectangle);
    glBufferData(GL_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

}

void OpenGLWidget::destroyVBOs()
{
    makeCurrent ();
    glDeleteBuffers(1, &vboVerticesRectangle);
    glDeleteBuffers (1, &vboColorsRectangle);
    glDeleteBuffers (1, &eboIndicesRectangle);
    glDeleteVertexArrays (1, &vaoRectangle);
    vboVerticesRectangle=0;
    eboIndicesRectangle=0;
    vboColorsRectangle=0;
    vaoRectangle=0;
}
