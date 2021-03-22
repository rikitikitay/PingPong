#include "ball.h"

Ball::Ball(QObject *parent)
    : QObject(parent), QGraphicsEllipseItem()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    srand(time(0));
    _x = (qrand()%180-90);
    _y = (qrand()%180-90);

    if ( abs(_y) > abs(_x)) // angle -pi/4 to pi/4 and  pi - (-pi/4)  to pi - pi/4
    {
        swap(_x,_y);
    }
    if(_x == 0 )
    {
        _x = _acceleration;
    }

    QPointF bufPoint = normalizeVector(_x,_y);
    _x = bufPoint.x();
    _y = bufPoint.y();
}

QPointF Ball::normalizeVector(qreal x1, qreal y1)
{
    qreal buf_x = x1/sqrt(x1*x1+y1*y1);
    qreal buf_y = y1/sqrt(x1*x1+y1*y1);
    x1 = _acceleration*buf_x;
    y1 = _acceleration*buf_y;
    return QPointF(x1,y1);
}

void Ball::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        if (!timer->isActive())
            signalSpace();
        //timer->start(25);
    }
    for (auto i: racket)
    {
        if (i->sight == Racket::Sight::left)
        {
            switch (event->key())
            {
            case Qt::Key::Key_W:
            case Qt::Key::Key_S:
            {
                i->_keysPressed += event->key();

            }
                break;
            }
        }
        if (i->sight == Racket::Sight::right)
            switch (event->key())
            {
            case Qt::Key::Key_Up:
            case Qt::Key::Key_Down:
            {
                i->_keysPressed += event->key();
            }
                break;
            }
    }

}

void Ball::keyReleaseEvent(QKeyEvent *event)
{
    for (auto i: racket)
    {
        if (i->sight == Racket::Sight::left)
        {
            switch (event->key())
            {
            case Qt::Key::Key_W:
            case Qt::Key::Key_S:
            {
                i->_keysPressed -= event->key();

            }
                break;
            }
        }
        if (i->sight == Racket::Sight::right)
            switch (event->key())
            {
            case Qt::Key::Key_Up:
            case Qt::Key::Key_Down:
            {
                i->_keysPressed -= event->key();
            }
                break;
            }
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

bool Ball::collides()
{
    for (auto item:  scene()->collidingItems(this))
    {
        if (dynamic_cast<Racket*>(item))
        {
            signalCollidingRacket();
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

    signalStartGame();
    setPos(x() + _x , y() + _y);
    if (collides())
    {
        _x = -_x;

        if (x() < 450)
        {

            _y = 2*((racket[0]->racketSpeed+1) / (abs(racket[0]->racketSpeed)+1)) +_y;
            QPointF bufPoint = normalizeVector(_x,_y);
            _x = bufPoint.x();
            _y = bufPoint.y();
            setPos(11 , y() + _y); // заменить 11
        }
        else
        {

            _y = 2*((racket[1]->racketSpeed+1) / (abs(racket[1]->racketSpeed)+1)) +_y; //
            QPointF bufPoint = normalizeVector(_x,_y);
            _x = bufPoint.x();
            _y = bufPoint.y();
            setPos(879 , y() + _y);
        }
    }
    else
    {

        if ((x() > 890) || (x() < 0))
        {
            signalGoal();
        }
        if ((y() > 590 ) || (y() < 0))
        {
            signalHorizontalWall();
            _y = -_y;
            qreal newY = (y() < 0) ? 0 : 590;
            setPos(x()  , newY);
        }
    }
}

Ball::~Ball()
{
    timer->deleteLater();
}

