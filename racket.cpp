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
    for (auto key: _keysPressed)
    {
        switch(key)
        {
        case Qt::Key::Key_S:
        {
            moveBy(0,_racketSpeed);
        }
            break;
        case Qt::Key::Key_W:
        {
            moveBy(0,-_racketSpeed);
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
}

void Racket::keyReleaseEvent(QKeyEvent *e)
{
    _keysPressed -= e->key();
}

