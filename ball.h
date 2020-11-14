#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Ball:  public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball (QObject *parent = nullptr);

private slots:
    void nextFrame();

private:
    void b_paint(QPainter *painter);
    QRectF boundingRect() const;

    QTimer *timer;
    QPixmap *spriteImage;
    int currentFrame;
};

#endif // BALL_H
