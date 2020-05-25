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
    unsigned value(int x, int y);
    void render(unsigned widthFrom, unsigned widthTo);
public:
    fractalRenderer();
    void stop();
    void setDimensions(unsigned x,unsigned y);
    void runRenderer(unsigned threads);
    bool isFinished(){return drawingFinished;}
    std::vector<std::vector<unsigned>> getImageData(){return imageData;}
};

#endif // FRACTALRENDERER_H
