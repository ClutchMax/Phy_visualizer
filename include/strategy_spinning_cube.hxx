#pragma once

#include "animation_strategy.hxx"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>

class SpinningCubeStrategy : public AnimationStrategy {
public:
    SpinningCubeStrategy();
    SpinningCubeStrategy(int height, int width, int line_width, int anim_duration);
    ~SpinningCubeStrategy() override;
    void updateAnim(int frame) override;

    std::string getType() override;
    void rotate();



private:
    int height;
    int width;
    int line_width;
    int anim_duration;
    std::string type;
    
    vtkSmartPointer<vtkImageData> image;
    vtkSmartPointer<vtkImageActor> imgActor;
    vtkSmartPointer<vtkRenderer> renderer;
};
