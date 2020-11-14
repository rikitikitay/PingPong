#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <ball.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(); // created a scene
    Ball* ball = new Ball();
    ball->setRect(0,0,200,200);
    scene->addItem(ball);
    QGraphicsView* view = new QGraphicsView(scene);
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;

}

