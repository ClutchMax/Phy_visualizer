#pragma once

#include "animation_strategy.hxx"
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

class SineWaveStrategy : public AnimationStrategy {
public:
    SineWaveStrategy();
    SineWaveStrategy(int height, int width, double freq, double amp);
    ~SineWaveStrategy() override;
    void updateAnim(int frame) override;

    
    std::string getType() override;


    // Class-only methods

    void setAmplitude(double ampl);
    vtkSmartPointer<vtkRenderer> getRenderer(){
        return renderer;
    }

private:
    std::string type;
    double frequency;
    double amplitude;
    int height;
    int width;

    vtkSmartPointer<vtkPoints> points;
    vtkSmartPointer<vtkPolyData> polyData;
    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkRenderer> renderer;
};