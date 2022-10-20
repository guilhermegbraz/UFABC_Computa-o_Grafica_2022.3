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

    void drawnSolidRectangle();
    void drawnSun();
    void drawnMoon();
    void drawnGround();

    GLuint vboVerticesRectangle{0};
    GLuint eboIndicesRectangle{0};
    GLuint vaoRectangle{0};

    GLuint vboGround{0};
    GLuint vboColorsGround{0};
    GLuint eboIndicesGround{0};
    GLuint vaoGround{0};



    GLuint vaoSun{0};
    GLuint vboVerticesSun{0};
    const unsigned int steps{719};

    GLuint vaoMoon{0};
    GLuint vboVerticesMoon{0};


    GLuint shaderProgram{0};

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

    float backgroundColor[3];



signals:

public slots:
    void toggleDarkMode(bool);
    void changeDayNight(int);

protected:
   void initializeGL();
   void resizeGL(int w, int h);
   void paintGL();


};

#endif // OPENGLWIDGET_H
