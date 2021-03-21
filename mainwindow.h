#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QPainter>

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


signals:

public slots:
    void ballSlot();
    void racketSlot();
    void wallSlot();
    void changeBallAcceleration();
    void moveRackets();

private:
    Ui::MainWindow *ui;
    Ball *ball;
    int points = 7;
    QTimer *racketsTimer;

};
#endif // MAINWINDOW_H
