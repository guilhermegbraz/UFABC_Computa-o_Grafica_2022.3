#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>//Mac OS use _4_1_Core
#include <QTimer>
#include <QElapsedTimer>
#include<QVector4D>
#include<vector>
#include<QFile>
#include<QtMath>
#include <cmath>
#include <QKeyEvent>
#include <QApplication>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();


    GLuint vboTarget{0};
    GLuint vboColorsTarget{0};
    GLuint eboIndicesTarget{0};
    GLuint vaoTarget{0};

    GLuint shaderProgram{0};

    GLuint vboVerticesRectangle{0};
    GLuint vboColorsRectangle{0};
    GLuint eboIndicesRectangle{0};
    GLuint vaoRectangle{0};

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

    GLuint vaoJanelaVidro{0};
    GLuint vboVerticesJanelaVidro{0};

    GLuint vaoJanelaBorda{0};
    GLuint vboVerticesJanelaBorda{0};

    float posx{0.0f};
    float posy{0.0f};

    float largura{0.15f};
    float altura{0.95};

    std::vector<QVector4D> vertices;
    std::vector<GLuint> indices;
    const unsigned int steps{719};


    float playerPosXOffset{0}; // deslocamento do player do eixo Y
    float playerPosX{posx + largura/6};

    float targetPosXOffset{2.0f};
    float targetPosX{0};

    void createVBOs();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();
    void changeDiagonal();

    void drawnFlaps();
    void drawnWindow();
    void DrawnRocket(GLuint & , GLuint &, GLuint &, GLuint &);
    void createPositionVBO(GLuint & , GLuint &, std::vector<QVector4D>);
    std::vector<QVector4D> createCircle(float, float, float, float);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    bool shooting{false};
    bool missileAvailable{false};
    bool reflectbleShootAvailable{false};

    int typeOfShoot{1};
    std::array<float, 2> projectilePos;

    float projectilePosOffset{8.0f};

    int numHits{0};
    bool shieldUp{true};

    int enemy{6};
    float enemySize{0.0f};

public slots:

    void animate();

signals:
    void updateHitsLabel(QString);
    void updateMissileStatus(QString);
    void updateEnemyShieldStatus(QString);
    void updateGameStatus(QString);

protected:
    void initializeGL();
    void resieGL(int w, int h);
    void paintGL();
    int numeroAleatorio(int , int );
    bool inverteuNaUltimaRodada{false};
    int damage{1};
private:
    QTimer timer;
    QElapsedTimer elapsedTime;
    bool blinkFlag{false};
    bool hitBlink{false};


};

#endif // OPENGLWIDGET_H
