#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QPair>
#include <QTime>
#include <QPainter>
#include <QDebug>
#include <qrandom.h>
#include <QLine>

#include "racket.h"

class Racket;

using namespace std;

class Ball:  public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball (QObject *parent = nullptr);
    void keyPressEvent (QKeyEvent* e) override;
    QPainterPath shape() const override;

    bool collides(qreal, qreal);

signals:
    void signalCollidingWall();
    void signalCollidingRacket();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

public slots:
    void move();

public:
    QTimer* timer = new QTimer();
     int _acceleration = 7;

private:
    int _x;
    int _y;

};

#endif // BALL_H
