// sine_animator.hxx
#pragma once

#include <QObject>
#include <QTimer>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>

class SineAnimator : public QObject {
    Q_OBJECT

public:
    SineAnimator(vtkGenericOpenGLRenderWindow* renderWindow, QObject* parent = nullptr);
    void start();

private slots:
    void updateFrame();

private:
    QTimer timer;
    int frame;

    vtkSmartPointer<vtkPoints> points;
    vtkSmartPointer<vtkPolyData> polyData;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkGenericOpenGLRenderWindow* renderWindow;
};
