#include "fractalrenderer.h"

fractalRenderer::fractalRenderer()
{
    width=800;
    height=600;
    workerThreadsAlive=0;
    imageData = std::vector<std::vector<unsigned> >
            (width, std::vector<unsigned> (height, 0));
    state=RendererState::running;
}

void fractalRenderer::setDimensions(unsigned x, unsigned y)
{
    width=x;
    height=y;
    imageData = std::vector<std::vector<unsigned>>
            (width, std::vector<unsigned> (height, 0));
}

bool fractalRenderer::isFinished()
{
    if(state==RendererState::drawingFinished)
        return true;
    else
        return false;
}

std::vector<std::vector<unsigned> > fractalRenderer::getImageData()
{
    return imageData;
}

void fractalRenderer::stop()
{
    state=RendererState::stopped;
    while(workerThreadsAlive>0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
