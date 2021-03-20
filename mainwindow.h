#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "racket.h"
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

private:
    Ui::MainWindow *ui;
    Ball *ball;

};
#endif // MAINWINDOW_H
