#ifndef FRACTALRENDERER_H
#define FRACTALRENDERER_H
#include <complex>
#include <QImage>
#include <QPainter>
#include <QThread>
#include <QtDebug>

class fractalRenderer :  QThread
{
     Q_OBJECT
private:
    QImage processedImage;
    unsigned width;
    unsigned height;
    QColor value(int x, int y);
public:
    fractalRenderer();
    void setDimentions(unsigned x,unsigned y)
    {width=x;height=y;}
    void runRenderer(unsigned threads);
    void run() override;
    QImage getImage(){return processedImage;}
};

#endif // FRACTALRENDERER_H
