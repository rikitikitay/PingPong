#include "ball.h"


Ball::Ball(QObject *parent)
    : QObject(parent), QGraphicsEllipseItem()
{
    //setRect(0,0,10,10);
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
    //_y = 0;
}

void Ball::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        timer->start(15);
    }
}

QRectF Ball::boundingRect() const
{
    return QRectF(0,0, 10,10);
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

bool Ball::collides(qreal x, qreal y)
{
    for (auto item:  scene()->collidingItems(this))
    {
        if (dynamic_cast<Racket*>(item))
        {
            //setPos(x,y);
            return true; //racket
        }
    }

    return false; // wall
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->drawEllipse(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Ball::move()
{
    setPos(x() + _x , y() + _y);
    if (collides(x(),y()))
    {
        signalCollidingRacket();
        //qDebug() << x() << " " << y() << " racket";
        //_y = -_y;
        _x = -_x;
        setPos(6 , y() + _y);
    }
    else
    {
        signalCollidingWall();
        if ((x() > 900) || (x() < 0))
        {
            //qDebug() << x() << " " << y() << " wall";
            _x = -_x;
            qreal newX = (x() < 0) ? 0 : 900;
            setPos(newX , y());
        }
        if ((y() > 600 ) || (y() < 0))
        {
            //qDebug() << x() << " " << y() << " wall";
            _y = -_y;
            qreal newY = (y() < 0) ? 0 : 600;
            setPos(x()  , newY);
        }

    }

}
