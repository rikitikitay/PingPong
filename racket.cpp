#include "racket.h"

Racket::Racket()
{
    setRect(0,0,5,100);
    _timer->start(25);

}

Racket::Racket(Racket::Sight s)
    :sight(s)
{  
    setRect(0,0,5,100);
    _timer->start(25);
}

QPainterPath Racket::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
