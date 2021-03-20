#ifndef RACKET_H
#define RACKET_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

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


public slots:
    void move();

signals:
    void gameSignal();

private:
    QTimer* timer = new QTimer();
    QSet<int> keysPressed;



};

#endif // RACKET_H
