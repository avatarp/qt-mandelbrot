#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    rMult=7;
    gMult=7;
    bMult=7;
    ui->setupUi(this);
    QApplication::processEvents();
    update();
    mandelbrot.setDimensions(ui->fractalCanvas->width(),
                             ui->fractalCanvas->height());
    mandelbrot.runRenderer(std::thread::hardware_concurrency());
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer->start(100);
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
    QImage fractal(ui->fractalCanvas->width(),
                   ui->fractalCanvas->height(),
                   QImage::Format_RGB32);

    qDebug()<<"imageData size X: "<<imageData.size();
    qDebug()<<"imageData size Y: "<<imageData[0].size();
    qDebug()<<"fractal size: "<<fractal.size();

    if(imageData[0].size()!=ui->fractalCanvas->height()
            || imageData.size()!=ui->fractalCanvas->width())
    {
        qDebug()<<"Paint event returned";
        return;
    }

    for(unsigned x=0;x<ui->fractalCanvas->width();x++)
    {
        for(unsigned y=0;y<ui->fractalCanvas->height();y++)
        {
            fractal.setPixel(x,y,qRgb((imageData[x][y]*rMult)%colorModulo,
                                      (imageData[x][y]*gMult)%colorModulo,
                                      (imageData[x][y]*bMult)%colorModulo));
        }
    }
    painter.drawImage(QPoint(ui->fractalCanvas->x(),
                             ui->fractalCanvas->y()),fractal);
}

void MainWindow::resizeEvent(QResizeEvent * /*event*/)
{
    mandelbrot.stop();
    mandelbrot.setDimensions(ui->fractalCanvas->width(),
                             ui->fractalCanvas->height());
    mandelbrot.runRenderer(std::thread::hardware_concurrency());
    if(updateTimer->isActive()==false)
        updateTimer->start(100);
}
