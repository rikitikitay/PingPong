#include "ball.h"
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include <qrandom.h>
#include <QLine>



Ball::Ball(QObject *parent)
    : QObject(parent), QGraphicsEllipseItem()
{
    setRect(0,0,10,10);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    srand(time(0));
    _x = _acceleration*(qrand()%4-2); // -2, -1, 0, 1, 2
    _y = _acceleration*(qrand()%4-2);
    if ( abs(_y) > abs(_x))
    {
        swap(_x,_y);
    }
    if(_x == 0 )
    {
        _x = _acceleration;
    }




}

void Ball::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        timer->start(15);
        qDebug() << "keyevent";
    }

}



void Ball::move()
{
    setPos(x() + _x , y() + _y);

    if ((x() > 900)||(x() < 0))
    {

        _x = -_x;

        setPos(x() + _x , y());

    }
    if ((y() > 600 ) || (y() < 0))
    {

        _y = -_y;
        setPos(x()  , y() + _y);

    }

   // qDebug() << x() << " " << scenePos().x();


}


