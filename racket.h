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
    Racket(Sight);
    void keyPressEvent (QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    QPainterPath shape() const override;
    int getRacketSpeed()
    {
        return racketSpeed;
    }


public slots:
    void move();

signals:
    void gameSignal();

public:
    int racketSpeed = 5;

private:
    QTimer* _timer = new QTimer();
    QSet<int> _keysPressed;

};

#endif // RACKET_H
