#include <ball.h>
#include <QTimer>
#include <QPainter>

Ball::Ball(QObject *parent)
    : QObject(parent), QGraphicsEllipseItem()
{
    currentFrame = 0;
    spriteImage = new QPixmap("C:\\Users\\ViP\\Documents\\Projects\\example\\explosion.png");

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Ball::nextFrame);
    timer->start(25);
}

QRectF Ball::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void Ball::b_paint(QPainter *painter) {
    painter->drawPixmap(-10, -10, *spriteImage, currentFrame, 0, 20, 20);
}

void Ball::nextFrame() {
    currentFrame += 20;
    if(currentFrame >= 300) currentFrame = 0;
    this->update(-10, -10, 20, 20);
}
