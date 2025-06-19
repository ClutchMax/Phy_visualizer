// sine_animator.hxx
#pragma once

#include <QObject>
#include <QTimer>
#include "animation_strategy.hxx"
#include <memory>
#include <string>

#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>



class Animator : public QObject {
    Q_OBJECT

public:
    Animator(vtkGenericOpenGLRenderWindow* renderWindow, 
        std::unique_ptr<AnimationStrategy> strategy,
        long duration,
        bool saveAnim = false,
        std::string savePath = "output/",
        QObject* parent = nullptr);

    void start();
    void pause();
    AnimationStrategy* getStrategy() const;
    long getDuration();
    long getFrame();
    
    void saveFrame();


protected slots:
    void updateFrame();
    

protected:
    QTimer timer;
    long frame = 0;
    long duration;
    bool saveAnim;
    std::string savePath;

    vtkGenericOpenGLRenderWindow* renderWindow;
    std::unique_ptr<AnimationStrategy> strategy;


signals:
    void frameUpdated(int currentFrame);
    
};


