#include "racket.h"

Racket::Racket()
{
    setRect(0,0,5,100);
}

Racket::Racket(Racket::Sight s)
    :sight(s)
{  
    setRect(0,0,5,100);
}
