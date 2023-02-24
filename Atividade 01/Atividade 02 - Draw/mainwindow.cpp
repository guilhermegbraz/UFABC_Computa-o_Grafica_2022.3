#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,620);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: selectedDraw(int d) {
    qDebug() << d;
    typeOfDraw = d;
    update(); //chama o paintEvent

}

void MainWindow::selectedPenColor(int id){
    const QColor colors[5] = {
        Qt::black,
        Qt::red,
        Qt::blue,
        Qt::green,
        Qt::gray,
    };
    color = colors[id];
    update();
}

void MainWindow::selectedBrushColor(int id){
    const QColor brushColors[6] = {
        QColorConstants::Transparent,
        Qt::black,
        Qt::red,
        Qt::blue,
        Qt::green,
        Qt::gray,
    };
     fillColor = brushColors[id];
    update();
}

void MainWindow::moveXCenter(int newX){
    Xcenter = 240 + 3.5 * newX;
    points[0].setX(Xcenter + 120);
    points[1].setX(Xcenter);
    points[2].setX(Xcenter + 240);

    update();
}
void MainWindow::moveYCenter(int newY){
    Ycenter = 25 + 3 * newY;
    points[0].setY(Ycenter);
    points[1].setY(Ycenter + 150);
    points[2].setY(Ycenter + 150);
    update();
}


void MainWindow :: paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(color);
    painter.setBrush(fillColor);

    switch (typeOfDraw) {
        case 0:

            break;
        case 1:
            painter.drawRect(Xcenter, Ycenter, 100, 300);
            break;
        case 2:
            painter.drawEllipse(Xcenter, Ycenter, 200, 125);
            break;
        case 3:
            painter.drawRect(Xcenter, Ycenter, 200, 200);
            break;
        case 4:
            painter.drawEllipse(Xcenter, Ycenter, 200, 200);
            break;
        case 5:
            painter.drawPolygon(points, 3);

            break;


        default:
            break;
    }

}

