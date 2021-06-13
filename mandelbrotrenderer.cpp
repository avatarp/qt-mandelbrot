#include "mandelbrotrenderer.h"

mandelbrotRenderer::mandelbrotRenderer()
{
    width=800;
    height=600;
    workerThreadsAlive=0;
    imageData = std::vector<std::vector<unsigned> >(width, std::vector<unsigned> (height, 0));
    state=RendererState::running;
    //iterationsLimit=42;
}


void mandelbrotRenderer::renderStart(unsigned threadsCount)
{
    if(threadsCount==0)
        threadsCount=1;

    if(state!=RendererState::running)
    {
        qDebug()<<"Reseting...";
        state=RendererState::running;
    }

    qDebug()<<"Starting"<<threadsCount<<"threads";

    renderStartTime=std::chrono::duration_cast< std::chrono::milliseconds >
            (std::chrono::system_clock::now().time_since_epoch());

    unsigned widthPart=width/threadsCount;
    std::vector<std::thread> workers(threadsCount);

    for(unsigned i=0;i<threadsCount;i++)
    {
        workers[i] = std::thread(&mandelbrotRenderer::render, this,
                                 i*widthPart,
                                 (i+1)*widthPart);
        workerThreadsAlive++;
        workers[i].detach();
    }
}

void mandelbrotRenderer::render(unsigned widthFrom, unsigned widthTo)
{
    for(unsigned x=widthFrom;x<widthTo;x++)
    {
        for(unsigned y=0;y<height;y++)
        {
            imageData[x][y]=value(x,y);
            if(state==RendererState::stopped){break;}
        }
        if(state==RendererState::stopped){break;}
    }

    lock.lock();
    workerThreadsAlive--;

    if(workerThreadsAlive==0)
    {
        std::chrono::milliseconds renderEndTime=std::chrono::duration_cast< std::chrono::milliseconds >
                (std::chrono::system_clock::now().time_since_epoch());
        renderEndTime-=renderStartTime;
        state=RendererState::drawingFinished;
        qDebug()<<"Finished in"<<renderEndTime.count()<<"ms";
    }
    lock.unlock();
}


unsigned mandelbrotRenderer::value(unsigned &x, unsigned &y)
{
    std::complex<float> point((float)x/width-1.5, (float)y/height-0.5);
    std::complex<float> z(0, 0);
    unsigned iterations = 0;

    while (abs(z) < 2 && iterations < 42)
    {
        z = z * z + point;
        iterations++;
    }
    return iterations;
}
