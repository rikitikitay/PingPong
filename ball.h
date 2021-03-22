#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QDebug>
#include <qrandom.h>
#include <cmath>
#include <QList>

#include "racket.h"

class Racket;

using namespace std;

class Ball:  public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball (QObject *parent = nullptr);
    ~Ball();
    void keyPressEvent (QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    QPainterPath shape() const override;
    bool collides();
    QPointF normalizeVector(qreal,qreal);

signals:
    void signalGoal();
    void signalCollidingRacket();
    void signalStartGame();
    void signalSpace();
    void signalHorizontalWall();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

public slots:
    void move();

public:
    QTimer* timer = new QTimer();
    int _acceleration = 10;
    QList<Racket*> racket;

    qreal _x;
    qreal _y;
};

#endif // BALL_H
