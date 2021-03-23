#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QFont>
#include <QSoundEffect>


#include <ball.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *target, QEvent *event);


signals:
    void signalGoal();

public slots:
    void changeBallAcceleration();
    void moveRackets();

private:
    Ui::MainWindow *ui;
    Ball *ball;
    QList<int> points = {0,0};
    QTimer *racketsTimer;
    QLabel *score;

    QSoundEffect *soundStart = new QSoundEffect();
    QSoundEffect *soundRebound = new QSoundEffect();
    QSoundEffect *soundSuccess = new QSoundEffect();
    QSoundEffect *soundWall = new QSoundEffect();

};
#endif // MAINWINDOW_H
