#pragma once

#include "animation_strategy.hxx"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>

class MatrixVisualizerStrategy : public AnimationStrategy {
public:
    MatrixVisualizerStrategy();
    MatrixVisualizerStrategy(int h, int w, int range, int line_width, int anim_dur, double** matrix);
    ~MatrixVisualizerStrategy() override;
    void updateAnim(int frame) override;

    std::string getType() override;
    vtkSmartPointer<vtkRenderer> getRenderer(){
        return renderer;
    }


private:
    int height;
    int width;
    std::string type;
    int anim_duration;
    int value_range;
    int line_width;
    double** matrix;

    vtkSmartPointer<vtkImageData> image;
    vtkSmartPointer<vtkImageActor> imgActor;
    vtkSmartPointer<vtkRenderer> renderer;
};