#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <complex>
#include <QPainter>
#include <QtDebug>

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
private:
    Ui::MainWindow *ui;
    QColor MainWindow::value(int x, int y);
};
#endif // MAINWINDOW_H
