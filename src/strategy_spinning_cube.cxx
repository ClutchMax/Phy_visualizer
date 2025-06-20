#include "../include/strategy_spinning_cube.hxx"

#include <cmath>
#include <limits>
#include <vtkTransform.h>
#include <vtkImageReslice.h>

SpinningCubeStrategy::SpinningCubeStrategy()
    : SpinningCubeStrategy(500, 800, 1);

SpinningCubeStrategy::SpinningCubeStrategy(int height, int width, int line_width, int anim_dur)
    : height(height), width(width), line_width(line_width), anim_duration(anim_dur) {

    }
    

SpinningCubeStrategy::~SpinningCubeStrategy() = default;


void SpinningCubeStrategy::rotate() {

}

void SpinningCubeStrategy::updateAnim(int frame){

}
