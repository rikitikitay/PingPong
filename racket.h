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
    QPainterPath shape() const override;



public slots:
    //void move();

signals:
    void gameSignal();

public:
    int racketSpeed = 12;
    int sight = left;
    QSet<int> _keysPressed;

private:
    QTimer* _timer = new QTimer();


};

#endif // RACKET_H
