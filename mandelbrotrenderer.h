#ifndef MANDELBROTRENDERER_H
#define MANDELBROTRENDERER_H

#include <complex>
#include <thread>
#include <mutex>
#include <QtDebug>
#include "fractalrenderer.h"

class mandelbrotRenderer: public fractalRenderer
{
private:
    std::chrono::milliseconds renderStartTime;
    unsigned value(unsigned &x, unsigned &y);
    void render(unsigned widthFrom, unsigned widthTo);
    unsigned iterationsLimit;
    double zoomX;
    double zoomY;
    double positionX;
    double positionY;
public:
    mandelbrotRenderer();
    void renderStart(unsigned threads);
};

#endif // MANDELBROTRENDERER_H



