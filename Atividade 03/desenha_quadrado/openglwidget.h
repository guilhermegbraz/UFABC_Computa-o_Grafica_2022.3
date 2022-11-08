#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>//Mac OS use _4_1_Core
#include <QTimer>
#include<QDebug>
#include<QVector4D>
#include<QVector3D>
#include<vector>
#include<QFile>
#include<QtMath>
#include <cmath>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
private:
    QTimer timer;    
    bool blinkFlag{false};
    bool isNight{false};

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

    void drawnSun();
    void drawnMoon();
    void drawnGround();
    void drawnFlaps();
    void drawnWindow();
    void createVBOs();
    void createShaders();

 std::vector<QVector4D> createCircle(float, float, float, float);
    void destroyVBOs();
    void destroyShaders();

    float backgroundColor[3];

    void DrawnRocket(GLuint & , GLuint &, GLuint &, GLuint &);
    void createPositionVBO(GLuint & , GLuint &, std::vector<QVector4D>);

    GLuint vboVerticesRectangle{0};
    GLuint vboColorsRectangle{0};
    GLuint eboIndicesRectangle{0};
    GLuint vaoRectangle{0};

    float playerPosYOffset{0}; // deslocamento do player do eixo Y
    float playerPosY{0};


    GLuint vboVerticesFlap1{0};
    GLuint eboIndicesFlap1{0};
    GLuint vaoFlap1{0};

    GLuint vboVerticesFlap2{0};
    GLuint eboIndicesFlap2{0};
    GLuint vaoFlap2{0};

    GLuint vaoFlapCentro{0};
    GLuint vboVerticesFlapCentro{0};

    GLuint vboVerticesTopo{0};
    GLuint eboIndicesTopo{0};
    GLuint vaoTopo{0};

    GLuint vboGround{0};
    GLuint vboColorsGround{0};
    GLuint eboIndicesGround{0};
    GLuint vaoGround{0};

    GLuint vaoJanelaVidro{0};
    GLuint vboVerticesJanelaVidro{0};

    GLuint vaoJanelaBorda{0};
    GLuint vboVerticesJanelaBorda{0};


    GLuint vaoSun{0};
    GLuint vboVerticesSun{0};
    const unsigned int steps{719};

    GLuint vaoMoon{0};
    GLuint vboVerticesMoon{0};


    GLuint shaderProgram{0};


    float posx{-0.8f};
    float posy{0.3f};

    float largura{0.15f};
    float altura{0.95};

    std::vector<QVector4D> vertices;
    std::vector<GLuint> indices;

signals:

public slots:
    void toggleDarkMode(bool);


protected:
   void initializeGL();
   void resizeGL(int w, int h);
   void paintGL();


};

#endif // OPENGLWIDGET_H
