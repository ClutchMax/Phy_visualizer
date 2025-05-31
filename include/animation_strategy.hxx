#pragma once

#include <vtkPoints.h>


class AnimationStrategy {
public:
    virtual ~AnimationStrategy() = default;
    virtual void updatePoints(vtkPoints* points, int frame) = 0;
    //virtual int getStrategyId();

private:
    int id_strat;
};