#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QPair>
#include <QTime>

using namespace std;



class Ball:  public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball (QObject *parent = nullptr);
    void keyPressEvent (QKeyEvent* e);
    QTimer* timer = new QTimer();

public slots:
    void move();

private:

    int _x;
    int _y;
    int _acceleration = 10;
};

#endif // BALL_H
