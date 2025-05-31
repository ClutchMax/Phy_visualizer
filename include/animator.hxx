// sine_animator.hxx
#pragma once

#include <QObject>
#include <QTimer>
#include "animation_strategy.hxx"
#include <memory>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
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
    vtkSmartPointer<vtkPoints> points;
    vtkSmartPointer<vtkPolyData> polyData;
    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkRenderer> renderer;

    std::unique_ptr<AnimationStrategy> strategy;
    
};


