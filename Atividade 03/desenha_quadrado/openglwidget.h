#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>//Mac OS use _4_1_Core
#include <QTimer>
#include<QVector4D>
#include<vector>
#include<QFile>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
private:
    QTimer timer;    
    bool blinkFlag{false};

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

    void drawnSolidRectangle();

    GLuint vboVerticesRectangle{0};
    GLuint vboColorsRectangle{0};
    GLuint eboIndicesRectangle{0};
    GLuint vaoRectangle{0};

    GLuint shaderProgram{0};


    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

signals:

public slots:
    void toggleDarkMode(bool);

protected:
   void initializeGL();
   void resizeGL(int w, int h);
   void paintGL();

};

#endif // OPENGLWIDGET_H
