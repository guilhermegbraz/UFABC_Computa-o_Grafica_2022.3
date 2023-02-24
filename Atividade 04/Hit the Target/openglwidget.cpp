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
    glClearColor(0.1, 0, 0.12, 1);

    qDebug("OpenGL Version: %s",glGetString(GL_VERSION));
    qDebug("GLSL Version: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));

    connect(&timer, &QTimer::timeout,this, &OpenGLWidget::animate);
    timer.start(0);

    elapsedTime.start();

    createShaders();
    createVBOs();
}

void OpenGLWidget :: resieGL(int w, int h){

}

void OpenGLWidget :: paintGL(){

    if(hitBlink) glClearColor(0.8,0.5,0.114,1);


    glClear(GL_COLOR_BUFFER_BIT);


    glUseProgram(shaderProgram);

    //target
    GLint locScaling{glGetUniformLocation(shaderProgram, "scaling")};
    GLint locTranslation{glGetUniformLocation(shaderProgram, "translation")};

    glBindVertexArray(vaoTarget);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 0);

    glUniform4f(locTranslation,targetPosX , 0.8f, 0, 0);
    glUniform1f(locScaling, 0.24f - enemySize);

    if(numHits > 10) {
        enemy = 3;
    }
    if(numHits > 20) {
        enemy = 0;
        emit updateGameStatus(QString("You Win!!!"));
    }
    glDrawElements(GL_TRIANGLES, enemy, GL_UNSIGNED_INT, 0);




    //shooting
    if(shooting) {

        switch (typeOfShoot) {
        case 1:

            glBindVertexArray(vaoTarget);
            glUniform4f(locTranslation,projectilePos[0] , projectilePos[1], 0, 0);
            glUniform1f(locScaling, 0.018f);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            break;

        case 2:
            glBindVertexArray(vaoFlapCentro);
            auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
            glUniform4f(locColor, 0.7416, 0.0008, 0.0016, 1);

            auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
            glUniform1i(locSolidColor, 1);
            glUniform1f(locScaling, 0.3f);

            glUniform4f(locTranslation,projectilePos[0] + (largura/2.8) , projectilePos[1], 0, 0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, steps);

            glUniform4f(locTranslation,projectilePos[0] - (largura/2.8) , projectilePos[1], 0, 0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
            break;
        }

    }

    //player
    DrawnRocket(vaoRectangle, vboVerticesRectangle, vboColorsRectangle, eboIndicesRectangle);
    drawnFlaps();
    drawnWindow();

    glClearColor(0.1, 0.1, 0.12, 1);
    hitBlink = false;

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

    glGenVertexArrays(1,&vaoTarget);
    glBindVertexArray(vaoTarget);

    glGenBuffers(1,&vboTarget);
    glBindBuffer(GL_ARRAY_BUFFER,vboTarget);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D),vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &vboColorsTarget);
    glBindBuffer (GL_ARRAY_BUFFER,vboColorsTarget);
    glBufferData (GL_ARRAY_BUFFER,colors.size()*sizeof(QVector4D),colors.data(),
                  GL_STATIC_DRAW);

    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboIndicesTarget);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesTarget);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indices.size() * sizeof (GLuint), indices.data() ,
                  GL_STATIC_DRAW);

    ///////FLAPS////////////////////////////////////////////////////////////////////////////////////////
    vertices.resize(3);
    indices.resize(3);

    vertices[0] = QVector4D(posx, posy - altura + 0.25 , 0, 1);
    vertices[1] = QVector4D( posx, posy - altura+0.05 , 0, 1);
    vertices[2] = QVector4D( posx - largura/1.8, posy - altura , 0, 1);

    createPositionVBO(vaoFlap1, vboVerticesFlap1, vertices);

    vertices[0] = QVector4D(posx + largura, posy - altura + 0.25 , 0, 1);
    vertices[1] = QVector4D( posx+ largura, posy - altura+0.05 , 0, 1);
    vertices[2] = QVector4D( posx + largura + largura/1.8, posy - altura , 0, 1);

    createPositionVBO(vaoFlap2, vboVerticesFlap2, vertices);

    //////////////////////////////topo/////////////////////////////////////////////////////////////
    vertices.resize(3);

    vertices[0] = QVector4D(posx, posy, 0, 1);
    vertices[1] = QVector4D( posx + largura, posy, 0, 1);
    vertices[2] = QVector4D( posx + largura/2, posy + (altura/4) , 0, 1);

    createPositionVBO(vaoTopo, vboVerticesTopo, vertices);// topo do foguete


    /////////////////////////////JANELA/////////////////////////////////////////////////////////////


    std::vector<QVector4D> verticesJanelaVidro = createCircle(posx + largura/2, posy - (altura/4),largura/3, largura/2 );
    createPositionVBO(vaoJanelaVidro, vboVerticesJanelaVidro, verticesJanelaVidro);//

    std::vector<QVector4D> verticesJanelaBorda = createCircle(posx + largura/2, posy - (altura/4),largura/2.5f, largura/1.65f );
    createPositionVBO(vaoJanelaBorda, vboVerticesJanelaBorda, verticesJanelaBorda);


    ///////////////FLAP CENTRO//////////////////////////////////////
    std::vector<QVector4D> verticesFlapCentro = createCircle(posx + largura/2, posy - altura + (altura/14), largura/11, altura/4.8f );
    createPositionVBO(vaoFlapCentro, vboVerticesFlapCentro, verticesFlapCentro);
}

void OpenGLWidget::destroyVBOs()
{
    makeCurrent ();
    glDeleteBuffers(1, &vboTarget);
    glDeleteBuffers (1, &vboColorsTarget);
    glDeleteBuffers (1, &eboIndicesTarget);
    glDeleteVertexArrays (1, &vaoTarget);

    glDeleteBuffers(1, &vboVerticesFlap1);
    glDeleteBuffers (1, &vboColorsRectangle);
    glDeleteBuffers (1, &eboIndicesRectangle);
    glDeleteVertexArrays (1, &vaoRectangle);
    glDeleteBuffers(1, &vboVerticesRectangle);

    glDeleteBuffers (1, &vboVerticesFlap2);
    glDeleteBuffers (1, &eboIndicesFlap1);
    glDeleteVertexArrays (1, &vaoFlap1);
    vboTarget=0;
    eboIndicesTarget=0;
    vboColorsTarget=0;
    vaoTarget=0;
    vboVerticesRectangle = 0;
    vboColorsRectangle=0;
    eboIndicesRectangle=0;
    vaoRectangle=0;
    eboIndicesFlap1=0;
    vboVerticesFlap1=0;
    vaoFlap1=0;
    vboVerticesFlap2=0;
    eboIndicesFlap2=0;
    vaoFlap2=0;
    vaoFlapCentro=0;
    vboVerticesFlapCentro=0;
    vboVerticesTopo=0;
    eboIndicesTopo=0;
    vaoTopo=0;
    vaoJanelaVidro=0;
    vboVerticesJanelaVidro=0;
    vaoJanelaBorda=0;
    vboVerticesJanelaBorda=0;
}



void OpenGLWidget::DrawnRocket(GLuint & vao, GLuint & vbo, GLuint & vboColors, GLuint & eboIndices) {

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;
    //glUniform4f(locColor, 0.827, 0.827, 0.827, 1);

    vertices.resize(6);
    colors.resize(6);
    indices.resize(6);

    ///////CORPO DO FOGUETE///////////////////////
    vertices[0] = QVector4D(posx, posy, 0, 1);
    vertices[1] = QVector4D(posx, posy - altura , 0, 1);
    vertices[2] = QVector4D(posx + largura/4, posy - altura - altura/20, 0, 1);
    vertices[3] = QVector4D(posx + 3 * largura/4, posy-altura - altura/20, 0, 1);
    vertices[4] = QVector4D( posx + largura, posy - altura , 0, 1);
    vertices[5] = QVector4D( posx + largura, posy , 0, 1);

    colors[0] = QVector4D(0.255, 0.255, 0.255, 1);
    colors[1] = QVector4D(0.255, 0.255, 0.255, 1);
    colors[2] = QVector4D(0.255, 0.255, 0.255, 1);
    colors[3] = QVector4D(0.827, 0.827, 0.827, 1);
    colors[4] = QVector4D(0.827, 0.827, 0.827, 1);
    colors[5] = QVector4D(0.827, 0.827, 0.827, 1);

    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 3; indices[4] = 4; indices[5] = 5;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);
    glGenBuffers (1, &vboColors);
    glBindBuffer (GL_ARRAY_BUFFER,vboColors);
    glBufferData (GL_ARRAY_BUFFER,colors.size()*sizeof(QVector4D),colors.data(),
                  GL_STATIC_DRAW);

    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);
    glGenBuffers (1, &eboIndices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indices.size() * sizeof (GLuint), indices.data() ,
                  GL_STATIC_DRAW);

    makeCurrent();
    glUseProgram(shaderProgram);
    GLint locScaling{glGetUniformLocation(shaderProgram, "scaling")};
    GLint locTranslation{glGetUniformLocation(shaderProgram, "translation")};

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 0);

    glBindVertexArray(vaoRectangle);

    glUniform4f(locTranslation, playerPosX,-0.6f , 0, 0);
    glUniform1f(locScaling, 0.34f);

    glDrawArrays(GL_POLYGON,0, 6);
}


void OpenGLWidget :: drawnFlaps() {
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.7416, 0.0008, 0.0016, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoFlap1);
    glDrawArrays(GL_POLYGON,0, 3);

    glUniform4f(locColor, 0.927, 0.001, 0.002, 1);

    glBindVertexArray(vaoFlap2);
    glDrawArrays(GL_TRIANGLE_FAN,0, 3);

    glBindVertexArray(vaoTopo);
    glDrawArrays(GL_TRIANGLE_FAN,0, 3);

    glBindVertexArray(vaoFlapCentro);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
}



void OpenGLWidget:: drawnWindow(){

    makeCurrent();
    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.22, 0.2, 0.2, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoJanelaBorda);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);


    glUniform4f(locColor, 0.01, 0.834, 0.9, 0.8);


    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoJanelaVidro);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
}

std::vector<QVector4D> OpenGLWidget:: createCircle(float posX, float posY, float raioX, float raioY){
    std::vector<QVector4D> verticesCircle;
    verticesCircle.resize(steps);
    for(unsigned int  i{0}; i < steps; i++){
        float os[2] = {posX, posY};
        float r[2] = {raioX, raioY};
        verticesCircle[i] = QVector4D(os[0] + r[0]*sin(i*(M_PI/180)),
                os[1] + r[1]*cos(i*(M_PI/180)), 0, 1);
    }
    return verticesCircle;
}

void OpenGLWidget:: createPositionVBO(GLuint & vao, GLuint & vbo, std::vector<QVector4D> vertices ) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A :
        playerPosXOffset = -2.0f;
        break;

    case Qt::Key_D :
        playerPosXOffset = 1.85f;

        break;

    case Qt::Key_Escape:
        QApplication::quit();

        break;

    case Qt::Key_1:
        if(!shooting){
            shooting = true;
            projectilePos[0] = playerPosX + (largura/6);
            projectilePos[1] = -0.513f;
            typeOfShoot = 1;
            damage = 1;
        }
        break;

    case Qt::Key_2:
        if(!shooting && missileAvailable){
            shooting = true;
            projectilePos[0] = playerPosX;
            projectilePos[1] = -altura/1.5;
            typeOfShoot = 2;
            missileAvailable = false;
            damage = 2;
            emit updateMissileStatus(QString("Missile shoot unavailable !"));
        }
        break;
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A :
        playerPosXOffset = 0.0f;
        break;

    case Qt::Key_D :
        playerPosXOffset = 0.0f;
        break;
    }
}

void OpenGLWidget::animate() {

    float elTime{elapsedTime.restart()/1000.0f};

    playerPosX += playerPosXOffset * elTime;

    if(playerPosX > 0.92f) playerPosX = 0.92f;
    if(playerPosX < -0.92f) playerPosX = -0.92f;


    //target
    targetPosX += targetPosXOffset * elTime;

    srand((unsigned)time(0)); //para gerar números aleatórios reais.
    int aleatorio = numeroAleatorio(1, 4);

    if((aleatorio == 2 || aleatorio == 4) && !inverteuNaUltimaRodada){
        targetPosXOffset = -targetPosXOffset;
        inverteuNaUltimaRodada = true;
        if(aleatorio == 2) {
            shieldUp = true;
            emit updateEnemyShieldStatus(QString("Enemy's shield is up"));
        }

    } else if(aleatorio != 2 && aleatorio != 4){
        inverteuNaUltimaRodada = false;

    }

    if(targetPosXOffset > 0) {

        if(targetPosX > 0.85f) {

            targetPosX = 0.85f;
            targetPosXOffset = -1 * targetPosXOffset;
        }
    }
    else {
        if(targetPosX < -0.85f) {

            targetPosX = -0.85f;
            targetPosXOffset = -targetPosXOffset;
        }
    }

    //projectile
    if(shooting) {
        projectilePos[1] += projectilePosOffset * elTime;
        float correcaoEixoX = 0.0f;

        if (typeOfShoot == 2) {
            correcaoEixoX = (largura/2.8f);
            projectilePosOffset = 15.0f;
        }

        if(
                (std::fabs(projectilePos[0] + correcaoEixoX - targetPosX) < 0.125f || std::fabs(projectilePos[0] - correcaoEixoX - targetPosX) < 0.125f )
                && std::fabs(projectilePos[1] - 0.8f) < 0.125f) {

            if(shieldUp){
                projectilePos[1] = 0.6f;
                projectilePosOffset = -2.0f;
                shieldUp = false;
                emit updateEnemyShieldStatus(QString("Enemy's shield is off"));
            }
            else{
                numHits+= damage;
                if(numHits > 8) enemySize += 0.01;
                emit updateHitsLabel(QString("Hits: %1").arg(numHits));
                shooting = false;
                hitBlink = true;
            }

            if(numHits % 4 == 0 && numHits >= 1){
                missileAvailable = true;
                emit updateMissileStatus(QString("Missile shoot available !"));
            }

        }

    } if(projectilePos[1] > 2.0f || projectilePos[1] < -1.1f ) {
        shooting = false;
        projectilePosOffset = 8.0f;
    }

    update();

}

int OpenGLWidget::numeroAleatorio(int menor, int maior) {
       return rand()%(maior-menor+1) + menor;
}



