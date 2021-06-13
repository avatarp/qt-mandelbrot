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
public:
    mandelbrotRenderer();
    void renderStart(unsigned threads);
};

#endif // MANDELBROTRENDERER_H



