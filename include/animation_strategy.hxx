#pragma once

#include <vtkPoints.h>
#include <string>
#include <vtkRenderer.h>


class AnimationStrategy {
public:
    virtual ~AnimationStrategy() = default;
    virtual void updateAnim(int frame) = 0;
    //virtual int getStrategyId();

    virtual std::string getType() = 0;
    virtual vtkSmartPointer<vtkRenderer> getRenderer() = 0;

protected:
    std::string type;
};