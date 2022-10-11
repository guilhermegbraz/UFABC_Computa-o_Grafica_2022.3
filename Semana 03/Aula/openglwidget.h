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
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    GLuint vboVertices{0};
    GLuint vboColors{0};
    GLuint eboIndices{0};
    GLuint vao{0};

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;
    GLuint shaderProgram{0};
    void createVBOs();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();
    void changeDiagonal();

public slots:
    void toggleDarkMode(bool);

protected:
    void initializeGL();
    void resieGL(int w, int h);
    void paintGL();

private:
    QTimer timer;
    bool blinkFlag{false};


};

#endif // OPENGLWIDGET_H
