#ifndef RACKET_H
#define RACKET_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

class Racket: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    enum Sight {
        left,
        right
    };
    Racket();
    Racket(Sight s);

public:
    int racketSpeed = 12;
    int sight;
    QSet<int> _keysPressed;
};

#endif // RACKET_H
