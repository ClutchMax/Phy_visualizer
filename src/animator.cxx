#include "../include/animator.hxx"
#include <vtkNamedColors.h>
#include <vtkPolyLine.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <cmath>


Animator::Animator(vtkGenericOpenGLRenderWindow* rwin, 
                    std::unique_ptr<AnimationStrategy> strat,
                    QObject* parent)
    : QObject(parent), 
      renderWindow(rwin), 
      strategy(std::move(strat))
{
    
    renderWindow->AddRenderer(strategy->getRenderer());
    renderWindow->SetSize(1000, 500);
    
    connect(&timer, &QTimer::timeout, this, &Animator::updateFrame);
}



void Animator::start() {
    timer.start(30);  // ~33 fps
}



void Animator::updateFrame(){
    strategy->updateAnim(frame);
    renderWindow->Render();

    frame = (frame + 1) % 360;
}


AnimationStrategy* Animator::getStrategy() const {
    return strategy.get();
}



