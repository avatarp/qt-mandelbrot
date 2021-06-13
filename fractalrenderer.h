#ifndef FRACTALRENDERER_H
#define FRACTALRENDERER_H

#include <complex>
#include <thread>
#include <mutex>
#include <QtDebug>

class fractalRenderer
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
    unsigned iterationsLimit;
    unsigned value(unsigned &x, unsigned &y);
    void render(unsigned widthFrom, unsigned widthTo);

public:
    fractalRenderer();
    virtual void stop();
    virtual void setDimensions(unsigned x,unsigned y);
    virtual void runRenderer(unsigned threads);
    virtual bool isFinished(){return drawingFinished;}
    virtual std::vector<std::vector<unsigned>> getImageData(){return imageData;}
};

#endif // FRACTALRENDERER_H
