#include "../include/animator.hxx"
#include <vtkNamedColors.h>
#include <vtkPolyLine.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

#include <cmath>
#include <sstream>
#include <filesystem>


Animator::Animator(vtkGenericOpenGLRenderWindow* rwin, 
                    std::unique_ptr<AnimationStrategy> strat,
                    long dur,
                    bool saveAnim,
                    std::string savePath,
                    QObject* parent)
    : QObject(parent), 
      renderWindow(rwin), 
      duration(dur),
      strategy(std::move(strat)),
      saveAnim(saveAnim),
      savePath(savePath)
{
    if(saveAnim && savePath != ""){
        std::filesystem::create_directory(savePath);
    }
    renderWindow->AddRenderer(strategy->getRenderer());
    renderWindow->SetSize(1000, 500);
    
    connect(&timer, &QTimer::timeout, this, &Animator::updateFrame);
}



void Animator::start() {
    timer.start(30);  // ~33 fps
}

void Animator::pause(){
    timer.stop();
}

void Animator::updateFrame(){
    strategy->updateAnim(frame);
    renderWindow->Render();
    if(saveAnim){
        saveFrame();
    }

    if(frame >= duration){
        saveAnim = false;
        timer.stop();
    }

    frame = (frame + 1) % (duration+1);
    emit frameUpdated(frame);
}


void Animator::saveFrame(){
    auto w2i = vtkSmartPointer<vtkWindowToImageFilter>::New();
    w2i->SetInput(renderWindow);
    w2i->Update();

    auto writer = vtkSmartPointer<vtkPNGWriter>::New();
    std::ostringstream filename;
    filename << savePath <<"frame_" << std::setw(4) << std::setfill('0') << frame << ".png";

    writer->SetFileName(filename.str().c_str());
    writer->SetInputConnection(w2i->GetOutputPort());
    writer->Write();
}




AnimationStrategy* Animator::getStrategy() const {
    return strategy.get();
}


long Animator::getDuration() {
    return duration;
}

long Animator::getFrame(){
    return frame;
}


