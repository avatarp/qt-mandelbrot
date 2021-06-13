#ifndef FRACTALRENDERER_H
#define FRACTALRENDERER_H

#include <complex>
#include <thread>
#include <mutex>
#include <QtDebug>

enum RendererState
{
    running,
    drawingFinished,
    stopped
};

class fractalRenderer
{
protected:
    unsigned width;
    unsigned height;
    RendererState state;
    std::vector<std::vector<unsigned>> imageData;
    unsigned workerThreadsAlive;
    std::mutex lock;
public:
    fractalRenderer();
    virtual void stop();
    virtual void setDimensions(unsigned x,unsigned y);
    virtual void renderStart(unsigned threads)=0;
    virtual bool isFinished();
    virtual std::vector<std::vector<unsigned>> getImageData();
};

#endif // FRACTALRENDERER_H
