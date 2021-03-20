#include "racket.h"
#include <QGraphicsRectItem>
#include <QDebug>


Racket::Racket()
{
    setRect(0,0,5,50);

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(25);



}

Racket::Racket(Racket::Sight)
{

}

void Racket::move()
{
    for (auto key: keysPressed)
    {
        switch(key)
        {
        case Qt::Key::Key_Down:
        case Qt::Key::Key_S:
        {
            moveBy(0,10);
        }
            break;
        case Qt::Key::Key_W:
        case Qt::Key::Key_Up:
        {
            moveBy(0,-10);
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
    keysPressed += e->key();
}

void Racket::keyReleaseEvent(QKeyEvent *e)
{
    keysPressed -= e->key();
}

