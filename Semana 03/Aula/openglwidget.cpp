#include "openglwidget.h"
#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

OpenGLWidget::~OpenGLWidget()
{
    destroyVBOs();
    destroyShaders();
}

void OpenGLWidget :: initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.75, 0.05, 1, 0.8);
    //QObject::connect(&timer, &QTimer::timeout, [&](){this->update();});
    //timer.start(200);
    qDebug("OpenGL Version: %s",glGetString(GL_VERSION));
    qDebug("GLSL Version: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));
    createShaders();
    createVBOs();
}

void OpenGLWidget :: resieGL(int w, int h){

}

void OpenGLWidget :: paintGL(){
    blinkFlag = !blinkFlag;
    //if(blinkFlag) {
    //glClearColor(1, 1, 1, 1);
    //} else{
    //glClearColor(0, 0, 0, 1);
    //}
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vaoGround);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLWidget :: toggleDarkMode(bool changeToDarkMode){

    makeCurrent();

    if(changeToDarkMode)
        glClearColor(0.05, 0.05,0.001,1);
    else
        glClearColor(1,1,1,1);
    update();
}


void OpenGLWidget::createShaders(){

    makeCurrent();
    destroyShaders();

    QFile vs(":/shaders/vshader1.glsl");
    QFile fs(":/shaders/fshader1.glsl");

    if(!vs.open(QFile::ReadOnly | QFile::Text))
       qDebug()<< "Nao consegui ler";//inserir mensagem de erro
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


void OpenGLWidget::createVBOs()
{
    makeCurrent();
    destroyVBOs();

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;

    vertices.resize(4);
    colors.resize(4);
    indices.resize(6);

    vertices[0] = QVector4D(-0.5, 0.5 , 0, 1);
    vertices[1] = QVector4D( 0.5, 0.5 , 0, 1);
    vertices[2] = QVector4D( 0.5, -0.5 , 0, 1);
    vertices[3] = QVector4D(-0.5, -0.5 , 0, 1);
    // Create colors for the vertices
    colors[0] = QVector4D(1, 0 , 0, 1); // Red
    colors[1] = QVector4D(0, 1, 0, 1); // Green
    colors[2] = QVector4D(0, 0, 1, 1); // Blue
    colors[3] = QVector4D(0.6, 0.6, 0, 1); // Yellow
    // Topology of the mesh ( square )
    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 2; indices[4] = 3; indices[5] = 0;
    glGenVertexArrays(1,&vaoGround);
    glBindVertexArray(vaoGround);
    glGenBuffers(1,&vboGround);
    glBindBuffer(GL_ARRAY_BUFFER,vboGround);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D),vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);
    glGenBuffers (1, &vboColorsGround);
    glBindBuffer (GL_ARRAY_BUFFER,vboColorsGround);
    glBufferData (GL_ARRAY_BUFFER,colors.size()*sizeof(QVector4D),colors.data(),
                  GL_STATIC_DRAW);

    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);
    glGenBuffers (1, &eboIndicesGround);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesGround);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indices.size() * sizeof (GLuint), indices.data() ,
                  GL_STATIC_DRAW);
}

void OpenGLWidget::destroyVBOs()
{
    makeCurrent ();
    glDeleteBuffers(1, &vboGround);
    glDeleteBuffers (1, &vboColorsGround);
    glDeleteBuffers (1, &eboIndicesGround);
    glDeleteVertexArrays (1, &vaoGround);
    vboGround=0;
    eboIndicesGround=0;
    vboColorsGround=0;
    vaoGround=0;
}


