#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QGraphicsScene* scene = new QGraphicsScene(); // created a scene

    ball = new Ball();
    scene->addItem(ball);
    ball->setPos(445,295);
    ball->setFlag(QGraphicsItem::ItemIsFocusable);
    ball->setFocus();

    ball->racket.push_back(new Racket(Racket::Sight::left));
    ball->racket.push_back(new Racket(Racket::Sight::right));

    scene->addItem(ball->racket.at(0));
    ball->racket.at(0)->setPos(5,250);


    scene->addItem(ball->racket.at(1));
    ball->racket.at(1)->setPos(890, 250);

    racketsTimer = new QTimer();
    connect(ball, &Ball::signalStartGame, this, &MainWindow::moveRackets);

    QGraphicsView* view = new QGraphicsView(scene);
    view->resize(900, 600);
    view->setFixedSize(900,600);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();

    QGraphicsRectItem* rect = new QGraphicsRectItem(0,0,900,600);
    scene->addItem(rect);
    rect->show();

    QTimer* ballAccTimer = new QTimer();
    connect(ballAccTimer, SIGNAL(timeout()), this, SLOT(changeBallAcceleration()));
    ballAccTimer->start(10000);

    score = new QLabel(view);
    score->setGeometry(QRect(0,15,900,50));

    QFont font = score->font();
    font.setPixelSize(30);

    score->setText(QString::number(points[0])+" : "+QString::number(points[1]));
    score->setFont(font);
    score->setStyleSheet("QLabel {color: rgb(0,0,0);}");
    score->setAlignment(Qt::AlignCenter);
    score->show();

    connect(ball, &Ball::signalCollidingWall, [=]()
    {
        if (ball->x() > 450)
        {
            points[0]++;
            QString colon = " : ";
            if (points[0] > 9)
                colon += " ";
            score->setText(QString::number(points[0])+colon+QString::number(points[1]));
        }
        else
        {
            points[1]++;
            QString colon = " : ";
            if (points[1] > 9)
                colon = "  : ";
            score->setText(QString::number(points[0])+colon+QString::number(points[1]));
        }
        signalGoal();
    });

    connect(this, &MainWindow::signalGoal, [=]()
    {
        ball->timer->stop();
        ball->setPos(445,295);
        ball->_x = (qrand()%180-90);
        ball->_y = (qrand()%180-90);

        if ( abs(ball->_y) > abs(ball->_x)) // angle -pi/4 to pi/4 and  pi - (-pi/4)  to pi - pi/4
        {
            swap(ball->_x,ball->_y);
        }

        if(ball->_x == 0 )
        {
            ball->_x = ball->_acceleration;
        }

        QPointF bufPoint = ball->normalizeVector(ball->_x,ball->_y);
        ball->_x = bufPoint.x();
        ball->_y = bufPoint.y();
        ball->_acceleration = 10;
        ball->racket.at(0)->setPos(5,250);
        ball->racket.at(1)->setPos(890, 250);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    ball->deleteLater();
    score->deleteLater();
    racketsTimer->deleteLater();
}

void MainWindow::changeBallAcceleration()
{
    ball->_acceleration = (ball->_acceleration < 20) ? (ball->_acceleration + 1) : 20;
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
