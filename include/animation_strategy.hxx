#pragma once

#include <vtkPoints.h>
#include <string>


class AnimationStrategy {
public:
    virtual ~AnimationStrategy() = default;
    virtual void updatePoints(vtkPoints* points, int frame) = 0;
    //virtual int getStrategyId();

    virtual std::string getType() = 0;

protected:
    std::string type;
};