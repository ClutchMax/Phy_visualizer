// sine_animator.hxx
#pragma once

#include <QObject>
#include <QTimer>
#include "animation_strategy.hxx"
#include <memory>

#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>

class Animator : public QObject {
    Q_OBJECT

public:
    Animator(vtkGenericOpenGLRenderWindow* renderWindow, 
        std::unique_ptr<AnimationStrategy> strategy,
        QObject* parent = nullptr);

    void start();
    AnimationStrategy* getStrategy() const;


protected slots:
    void updateFrame();
    

protected:
    QTimer timer;
    int frame = 0;

    vtkGenericOpenGLRenderWindow* renderWindow;
    std::unique_ptr<AnimationStrategy> strategy;
    
};


