#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene(); // created a scene

    ball = new Ball();
    scene->addItem(ball);
    ball->setPos(455,295);
    ball->setFlag(QGraphicsItem::ItemIsFocusable);
    ball->setFocus();

    Racket* racket = new Racket();
    scene->addItem(racket);
    racket->setPos(0,275);
    racket->setFlag(QGraphicsItem::ItemIsFocusable);
    racket->setFocus();

    QGraphicsView* view = new QGraphicsView(scene);
    view->resize(900, 600);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();

    QGraphicsRectItem* rect = new QGraphicsRectItem(view->rect());
    scene->addItem(rect);
    rect->show();

    QLine line(0,300, 900, 300);
    scene->addLine(line);

    connect(racket, &Racket::gameSignal, this, &MainWindow::ballSlot);
    connect(ball, &Ball::signalCollidingRacket, this, &MainWindow::racketSlot);
    connect(ball, &Ball::signalCollidingWall, this, &MainWindow::wallSlot);

    QTimer *ballAccTimer = new QTimer();
    connect(ballAccTimer, SIGNAL(timeout()), this, SLOT(changeBallAcceleration()));
    ballAccTimer->setInterval(60000);
    ballAccTimer->start(25);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ballSlot()
{
    ball->timer->start(20);
}

void MainWindow::racketSlot()
{
    points++;
}

void MainWindow::wallSlot()
{
    points--;
}

void MainWindow::changeBallAcceleration()
{
    ball->_acceleration += points;
    qDebug() << "acceleration " << ball->_acceleration;

}
