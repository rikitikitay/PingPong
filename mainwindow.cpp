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

    ball->racket.push_back(new Racket(Racket::Sight::left));

    scene->addItem(ball->racket.at(0));
    ball->racket.at(0)->setPos(5,275);

    ball->racket.push_back(new Racket(Racket::Sight::right));
    scene->addItem(ball->racket.at(1));
    ball->racket.at(1)->setPos(890, 275);

    racketsTimer = new QTimer();
    connect(ball, &Ball::signalStartGame, this, &MainWindow::moveRackets);

    QGraphicsView* view = new QGraphicsView(scene);
    view->resize(900, 600);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();

    QGraphicsRectItem* rect = new QGraphicsRectItem(0,0,900,600);
    scene->addItem(rect);
    rect->show();

    QLine line(0,300, 900, 300);
    scene->addLine(line);


    connect(ball, &Ball::signalCollidingRacket, this, &MainWindow::racketSlot);
    connect(ball, &Ball::signalCollidingWall, this, &MainWindow::wallSlot);

    QTimer* ballAccTimer = new QTimer();
    connect(ballAccTimer, SIGNAL(timeout()), this, SLOT(changeBallAcceleration()));
    ballAccTimer->start(10000);

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
    // qDebug() << "rot ball racket " << ball->rotation();
}

void MainWindow::wallSlot()
{
    //points--;
    // qDebug() << "rot ball wall " << ball->rotation();
}

void MainWindow::changeBallAcceleration()
{
    // ball->_acceleration += points;
    ball->_acceleration = (ball->_acceleration < 20) ? (ball->_acceleration + 1) : 20;


    qDebug() << ball->_acceleration;

    //ball->_y += ball->_acceleration;
}

void MainWindow::moveRackets()
{
    for (auto i: ball->racket)
    {
        i->racketSpeed = 12;
        if (i->_keysPressed.isEmpty())
            i->racketSpeed = 0;
        for (auto j: i->_keysPressed)
        {
            switch(j)
            {
            case Qt::Key::Key_S:
            case Qt::Key::Key_Down:
            {
                i->racketSpeed = abs(i->racketSpeed);
                if (i->y() < 500)
                    i->moveBy(0,i->racketSpeed);

            }
                break;
            case Qt::Key::Key_W:
            case Qt::Key::Key_Up:
            {
                i->racketSpeed = -abs(i->racketSpeed);
                if (i->y() > 0)
                    i->moveBy(0,i->racketSpeed);
            }
                break;
            }
        }
    }
}
