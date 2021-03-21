#include "racket.h"

Racket::Racket()
{
    setRect(0,0,5,100);

    connect(_timer, SIGNAL(timeout()), this, SLOT(move()));
    _timer->start(25);

}

Racket::Racket(Racket::Sight)
{

}

QPainterPath Racket::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Racket::move()
{
    if (_keysPressed.isEmpty())
        racketSpeed = 0;
    racketSpeed = 5;
    for (auto key: _keysPressed)
    {
        switch(key)
        {
        case Qt::Key::Key_S:
        {
            racketSpeed = abs(racketSpeed);
            moveBy(0,racketSpeed);

        }
            break;
        case Qt::Key::Key_W:
        {
            racketSpeed = -abs(racketSpeed);
            moveBy(0,racketSpeed);

        }
            break;
        case Qt::Key::Key_Space:
        {
            gameSignal();
        }
            break;
        }
    }
}

void Racket::keyPressEvent(QKeyEvent *e)
{
    _keysPressed += e->key();
    // qDebug() << _keysPressed << " press";
}

void Racket::keyReleaseEvent(QKeyEvent *e)
{
    _keysPressed -= e->key();
    //qDebug() << _keysPressed << " release";
}

