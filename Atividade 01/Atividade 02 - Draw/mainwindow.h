#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QPainter>
#include<Collor.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);


    int Xcenter{420};
    int Ycenter{200};
    QPointF points[3]={
        QPointF(Xcenter + 90, Ycenter),
        QPointF(Xcenter+90 - 120, Ycenter + 150),
        QPointF(Xcenter+90 + 120, Ycenter + 150),
    };

public slots:
    void selectedDraw(int);
    void selectedPenColor(int);
    void moveXCenter(int);
    void moveYCenter(int);
    void selectedBrushColor(int);

private:
    Ui::MainWindow *ui;
    int typeOfDraw{0};

    QColor color{Qt::black};
    QColor fillColor{QColorConstants::Transparent};

};
#endif // MAINWINDOW_H
