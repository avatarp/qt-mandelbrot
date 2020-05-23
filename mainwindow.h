#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QtDebug>
#include <QTimer>
#include "fractalrenderer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();  
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWindow *ui;
    unsigned rMult, gMult, bMult;
    fractalRenderer mandelbrot;
    QTimer *updateTimer;
    std::vector<std::vector<unsigned>> imageData;
    const unsigned colorModulo=256;
};
#endif // MAINWINDOW_H
