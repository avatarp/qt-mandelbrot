#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mandelbrot.setDimentions(this->width(),this->height());
    mandelbrot.runRenderer(std::thread::hardware_concurrency());
    rMult=1;
    gMult=1;
    bMult=10;
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer->start(100);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent * /*event*/)
{
    if(mandelbrot.isFinished() && updateTimer->isActive())
    {
        updateTimer->stop();
    }
    imageData=mandelbrot.getImageData();
    QPainter painter(this);
    QImage fractal(this->width(),this->height(),QImage::Format_RGB32);

    for(unsigned x=0;x<this->width();x++)
    {
        for(unsigned y=0;y<this->height();y++)
        {
            fractal.setPixel(x,y,qRgb((imageData[x][y]*rMult)%colorModulo,
                                      (imageData[x][y]*gMult)%colorModulo,
                                      (imageData[x][y]*bMult)%colorModulo));
        }
    }
    painter.drawImage(QPoint(0,0),fractal);
}

void MainWindow::resizeEvent(QResizeEvent * /*event*/)
{
    mandelbrot.stop();
    mandelbrot.setDimentions(this->width(),this->height());
    mandelbrot.runRenderer(std::thread::hardware_concurrency());
    if(updateTimer->isActive()==false){updateTimer->start(100);}

}
