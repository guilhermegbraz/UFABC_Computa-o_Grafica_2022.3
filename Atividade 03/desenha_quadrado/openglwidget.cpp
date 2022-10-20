#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void OpenGLWidget::initializeGL()
{
   initializeOpenGLFunctions();
   backgroundColor[0] = 0.2;
   backgroundColor[1] = 0.671;
   backgroundColor[2] = 0.976;
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

      if(isNight){
          qDebug() << "Esta de noite";
          drawnMoon();
      } else{
            drawnSun();
      }
     drawnGround();
     drawnSolidRectangle();
}

void OpenGLWidget :: drawnSolidRectangle() {
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.827, 0.827, 0.827, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoRectangle);

    glDrawArrays(GL_TRIANGLE_FAN,0, 4);
}

void OpenGLWidget::drawnGround(){
    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;

    vertices.resize(4);
    colors.resize(4);
    indices.resize(6);

    vertices[0] = QVector4D(-1, -1 , 0, 1);
    vertices[1] = QVector4D( 1, -1 , 0, 1);
    vertices[2] = QVector4D( 1, -0.5 , 0, 1);
    vertices[3] = QVector4D(-1, -0.5 , 0, 1);
    // Create colors for the vertices
    colors[0] = QVector4D(0, 0.2 , 0, 1); // Red
    colors[1] = QVector4D(0, 0.2, 0, 1); // Green
    colors[2] = QVector4D(0, 0.6, 0, 1); // Blue
    colors[3] = QVector4D(0, 0.6, 0, 1); // Yellow
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

    makeCurrent();
    glUseProgram(shaderProgram);
    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 53);

    glBindVertexArray(vaoGround);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void OpenGLWidget:: drawnSun(){
    makeCurrent();
    glUseProgram(shaderProgram);
    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.976, 0.843, 0.110, 1);
    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);
    glBindVertexArray(vaoSun);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
}


void OpenGLWidget:: drawnMoon(){

    glGenVertexArrays(1, &vaoMoon);
    glBindVertexArray(vaoMoon);

    std::vector<QVector4D> verticesMoon;
    verticesMoon.resize(steps);
    for(unsigned int  i{0}; i < steps; i++){
        float os[2] = {0.7, 0.62};
        float r[2] = {0.12, 0.18};
        verticesMoon[i] = QVector4D(os[0] + r[0]*sin(i*(M_PI/180)),
                os[1] + r[1]*cos(i*(M_PI/180)), 0, 1);
    }


    glGenBuffers(1, &vboVerticesMoon);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesMoon);
    glBufferData(GL_ARRAY_BUFFER, verticesMoon.size()*sizeof(QVector4D), verticesMoon.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);

    makeCurrent();
    glUseProgram(shaderProgram);
    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.976, 0.943, 1, 1);
    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);
    glBindVertexArray(vaoMoon);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
}

void OpenGLWidget::changeDayNight(int response){
    makeCurrent();
    if(response == 0) {

        backgroundColor[0] = 0.2;
        backgroundColor[1] = 0.671;
        backgroundColor[2] = 0.976;
    } else{

        backgroundColor[0] = 0.145;
        backgroundColor[1] = 0.157;
        backgroundColor[2] = 0.314;
    }

    glClearColor(backgroundColor[0],backgroundColor[1],backgroundColor[2],1);
    update();
}

void OpenGLWidget::toggleDarkMode(bool changeToDarkMode)
{
    makeCurrent();
    if(changeToDarkMode){
        isNight = true;
        glClearColor(0.145,0.157,0.314,1);
    }
    else{
        isNight = false;
        glClearColor(0.2,0.671,0.976,1);
    }
    update();
}



void OpenGLWidget:: createVBOs() {
    makeCurrent();
    destroyVBOs();

    std::vector<QVector4D> vertices;
    std::vector<GLuint> indices;

    vertices.resize(4);
    indices.resize(4);

    float posx{-0.8f};
    float posy{0.3f};

    float largura{0.2f};
    float altura{0.95};

    vertices[0] = QVector4D(posx, posy - altura , 0, 1);
    vertices[1] = QVector4D( posx + largura, posy - altura , 0, 1);
    vertices[2] = QVector4D( posx + largura, posy , 0, 1);
    vertices[3] = QVector4D(posx, posy, 0, 1);

    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 2; indices[4] = 3; indices[5] = 0;

    glGenVertexArrays(1, &vaoRectangle);
    glBindVertexArray(vaoRectangle);

    glGenBuffers(1, &vboVerticesRectangle);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesRectangle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &eboIndicesRectangle);
    glBindBuffer(GL_ARRAY_BUFFER, eboIndicesRectangle);
    glBufferData(GL_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    /////////////DRWANING THE SUN//////////////////////////////////
    glGenVertexArrays(1, &vaoSun);
    glBindVertexArray(vaoSun);

    std::vector<QVector4D> verticesSun;
    verticesSun.resize(steps);
    for(unsigned int  i{0}; i < steps; i++){
        float os[2] = {0.6, 0.65};
        float r[2] = {0.24, 0.32};
        verticesSun[i] = QVector4D(os[0] + r[0]*sin(i*(M_PI/180)),
                os[1] + r[1]*cos(i*(M_PI/180)), 0, 1);
    }

    glGenBuffers(1, &vboVerticesSun);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesSun);
    glBufferData(GL_ARRAY_BUFFER, verticesSun.size()*sizeof(QVector4D), verticesSun.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);

    /////////////DRWANING THE Moon//////////////////////////////////
    /*glGenVertexArrays(1, &vaoMoon);
    glBindVertexArray(vaoMoon);

    std::vector<QVector4D> verticesMoon;
    verticesMoon.resize(steps);
    for(unsigned int  i{0}; i < steps; i++){
        float os[2] = {0.7, 0.62};
        float r[2] = {0.12, 0.18};
        verticesMoon[i] = QVector4D(os[0] + r[0]*sin(i*(M_PI/180)),
                os[1] + r[1]*cos(i*(M_PI/180)), 0, 1);
    }


    glGenBuffers(1, &vboVerticesMoon);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesMoon);
    glBufferData(GL_ARRAY_BUFFER, verticesMoon.size()*sizeof(QVector4D), verticesMoon.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);*/
}

void OpenGLWidget::destroyVBOs()
{
    makeCurrent ();
    glDeleteBuffers(1, &vboVerticesRectangle);
    glDeleteBuffers (1, &eboIndicesRectangle);
    glDeleteVertexArrays (1, &vaoRectangle);
    glDeleteVertexArrays (1, &vaoSun);
    glDeleteVertexArrays (1, &vboVerticesSun);

    glDeleteVertexArrays (1, &vaoMoon);
    glDeleteVertexArrays (1, &vboVerticesMoon);

    glDeleteBuffers(1, &vboGround);
    glDeleteBuffers (1, &vboColorsGround);
    glDeleteBuffers (1, &eboIndicesGround);
    glDeleteVertexArrays (1, &vaoGround);

    vboGround=0;
    eboIndicesGround=0;
    vboColorsGround=0;
    vaoGround=0;
    vboVerticesRectangle=0;
    eboIndicesRectangle=0;
    vaoRectangle=0;
    vaoSun=0;
    vboVerticesSun=0;
    vaoMoon=0;
    vboVerticesMoon=0;
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
