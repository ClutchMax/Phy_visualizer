#pragma once

#include "animation_strategy.hxx"

class SineWaveStrategy : public AnimationStrategy {
public:
    SineWaveStrategy();
    SineWaveStrategy(double freq, double amp);
    ~SineWaveStrategy() override;
    void updatePoints(vtkPoints* points, int frame) override;

    void setAmplitude(double ampl);

private:
    double frequency;
    double amplitude;
};