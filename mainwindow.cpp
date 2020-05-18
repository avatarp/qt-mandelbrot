#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(1);
    for(unsigned x=0;x<this->width();x++)
    {
        for(unsigned y=0;y<this->height();y++)
        {
            pen.setColor(value(x,y));
            painter.setPen(pen);
            painter.drawPoint(x,y);
        }
        qDebug()<<"x="<<x<<endl;
    }

}

QColor MainWindow::value(int x, int y)
{
    std::complex<float> point((float)x/this->width()-1.5, (float)y/this->height()-0.5);
    std::complex<float> z(0, 0);
        unsigned nb_iter = 0;
        while (abs(z) < 2 && nb_iter <= 34) {
               z = z * z + point;
               nb_iter++;
        }
        if (nb_iter < 34)
            return QColor::fromRgb((nb_iter*10)%256,
                                   (nb_iter*20)%256,
                                   (nb_iter*10)%256);
        else return QColor::fromRgb(0);
}


