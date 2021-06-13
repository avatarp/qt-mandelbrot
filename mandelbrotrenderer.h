#ifndef MANDELBROTRENDERER_H
#define MANDELBROTRENDERER_H

#include <complex>
#include <thread>
#include <mutex>
#include <QtDebug>
#include "fractalrenderer.h"

class mandelbrotRenderer: fractalRenderer
{
private:
    std::vector<std::vector<unsigned>> imageData;
    unsigned width;
    unsigned height;
    unsigned threadsAlive;
    std::mutex lock;
    std::chrono::milliseconds renderStartTime;
    bool drawingFinished;
    bool isStopped;
    unsigned value(unsigned &x, unsigned &y);
    void render(unsigned widthFrom, unsigned widthTo);
public:
    mandelbrotRenderer();
    void stop();
    void setDimensions(unsigned x,unsigned y);
    void runRenderer(unsigned threads);
    bool isFinished(){return drawingFinished;}
    std::vector<std::vector<unsigned>> getImageData(){return imageData;}
};

#endif // MANDELBROTRENDERER_H



